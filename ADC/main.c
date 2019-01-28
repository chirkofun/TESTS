#include <ch.h>
#include <hal.h>
#include <chprintf.h>

#define ADC1_NUM_CHANNELS   1
#define ADC1_BUF_DEPTH      1

static adcsample_t samples1[ADC1_NUM_CHANNELS * ADC1_BUF_DEPTH];

int value;

/*
 * ADC streaming callback.
 */
static void ADC_CB(ADCDriver *adcp, adcsample_t *buffer, size_t n)
{
  adcp = adcp;
  n = n;
  value = buffer[0];
}

/*
 * ADC errors callback, should never happen.
 */
static void ADC_ErrCB(ADCDriver *adcp, adcerror_t err) {

  adcp = adcp;
  err = err;
}


/*
 * Serial UART configuration.
 */
static const SerialConfig UARTcfg = {
        .speed  = 115200,
        .cr1    = 0,
        .cr2    = 0,
        .cr3    = 0
    };

static const ADCConversionGroup ADC_Grpcfg = {
  .circular     = true,                     // working mode = looped
  /* Buffer will continue writing to the beginning when it come to the end */
  .num_channels = ADC1_NUM_CHANNELS,       // number of channels
  .end_cb       = ADC_CB,              // after ADC conversion ends - call this func
  /* Don`t forget about depth of buffer */
  .error_cb     = ADC_ErrCB,         // in case of errors, this func will be called
  .cr1          = 0,
  /* Cause we don`t need to write something to the register */
  .cr2          = ADC_CR2_EXTEN_RISING | ADC_CR2_EXTSEL_SRC(0b1001),  // Commutated from GPT
  /* 9 means 0b1001, and from RM (p.449) it is GPT1 */
  /* ADC_CR2_EXTEN_RISING - means to react on the rising signal (front) */
  .smpr1        = ADC_SMPR1_SMP_AN10(ADC_SAMPLE_144),       // for AN10 - 144 samples
  .smpr2        = 0,        // null
  .sqr1         = ADC_SQR1_NUM_CH(ADC1_NUM_CHANNELS),   //
  /* Usually this field is set to 0 as config already know the number of channels (.num_channels) */
  .sqr2         = 0,
  .sqr3         = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN10)      // sequence of channels

  /* If we can macro ADC_SQR2_SQ... we need to write to .sqr2 */
};

/*
 * GPT1 configuration. This timer is used as trigger for the ADC.
 */
static const GPTConfig GPT1cfg = {
    .frequency    = 100000,
    .callback     = NULL,
    .cr2          = TIM_CR2_MMS_1,
    .dier         = 0U
};

/*
 * Serial 7 UART Initialization.
 */
void sd7_init(void)
{
    sdStart( &SD7, &UARTcfg );
    palSetPadMode( GPIOE, 8, PAL_MODE_ALTERNATE(8) );    // TX
    palSetPadMode( GPIOE, 7, PAL_MODE_ALTERNATE(8) );    // RX
}

int main(void)
{
    chSysInit();
    halInit();

    sd7_init();

    gptStart(&GPTD1, &GPT1cfg);

    // ADC driver
    adcStart(&ADCD1, NULL);

    palSetLineMode( LINE_ADC123_IN10, PAL_MODE_INPUT_ANALOG );  // PC0

    adcStartConversion(&ADCD1, &ADC_Grpcfg, samples1, ADC1_BUF_DEPTH);
    gptStartContinuous(&GPTD1, GPT1cfg.frequency/200);          // how often we need ADC value
    /* Just set the limit (interval) of timer counter, you can use this function
    not only for ADC triggering, but start infinite counting of timer for callback processing */

    while (true)
       {
           chprintf(((BaseSequentialStream *)&SD7), "%d\n\r", value);
           chThdSleepMilliseconds( 200 );
       }
}
