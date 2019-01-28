#include <ch.h>
#include <hal.h>
#include <chprintf.h>

static const SerialConfig UARTcfg = {
        .speed  = 9600,
        .cr1    = 0,
        .cr2    = 0,
        .cr3    = 0
    };

PWMConfig PWM3cfg = {
    .frequency = 500000,
    .period    = 10000,
    .callback  = NULL,
    .channels  = {
                  {.mode = PWM_OUTPUT_DISABLED, .callback = NULL}, // Channel 1 is working CH1 = PE9
                  {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
                  {.mode = PWM_OUTPUT_ACTIVE_HIGH,    .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED,  .callback = NULL}
                  },
    .cr2        = 0,
    .dier       = 0
};

void pwm3_init(void)
{
    palSetPadMode( GPIOB, 0, PAL_MODE_ALTERNATE(2) );
    pwmStart(&PWMD3 , &PWM3cfg );

}

void sd7_init(void)
{
    sdStart( &SD7, &UARTcfg );
    palSetPadMode( GPIOE, 8, PAL_MODE_ALTERNATE(8) );    // TX
    palSetPadMode( GPIOE, 7, PAL_MODE_ALTERNATE(8) );    // RX
}

int main(void)
{
    int bright = 0;

    chSysInit();
    halInit();

    sd7_init();
    pwm3_init();

    sdWrite(&SD7, "Press W or S \r\n", 16);

    while (true)
       {
           char sym = sdGet(&SD7);

           if ((sym == 'w')||(sym == 'W'))
           {
               bright += 1000;
               if (bright>10000) bright = 10000;
               sdWrite(&SD7, "Bright +10% \r\n", 16);
           }
           else if ((sym == 's')||(sym == 'S'))
           {
               bright -= 1000;
               if (bright<0) bright = 0;
               sdWrite(&SD7, "Bright -10% \r\n", 16);
           }

           pwmEnableChannel( &PWMD3, 2, bright );
           chThdSleepMilliseconds( 300 );
       }
}
