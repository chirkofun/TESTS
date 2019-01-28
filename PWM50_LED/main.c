#include <ch.h>
#include <hal.h>

#include <chprintf.h>

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

PWMConfig PWM4cfg = {
    .frequency = 500000,
    .period    = 10000,
    .callback  = NULL,
    .channels  = {
                  {.mode = PWM_OUTPUT_DISABLED, .callback = NULL}, // Channel 1 is working CH1 = PE9
                  {.mode = PWM_OUTPUT_ACTIVE_HIGH,    .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED,    .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED,    .callback = NULL}
                  },
    .cr2        = 0,
    .dier       = 0
};

PWMConfig PWM1cfg = {
    .frequency = 500000,
    .period    = 10000,
    .callback  = NULL,
    .channels  = {
                  {.mode = PWM_OUTPUT_DISABLED, .callback = NULL}, // Channel 1 is working CH1 = PE9
                  {.mode = PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED,    .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED,  .callback = NULL}
                  },
    .cr2        = 0,
    .dier       = 0
};

int main(void)
{
    unsigned int bright;

    chSysInit();
    halInit();

    palSetLineMode( PAL_LINE( GPIOB, 0 ),  PAL_MODE_ALTERNATE(2) );
    palSetLineMode( PAL_LINE( GPIOB, 7 ),  PAL_MODE_ALTERNATE(2) );
    palSetLineMode( PAL_LINE( GPIOB, 14 ),  PAL_MODE_ALTERNATE(1) );

    pwmStart( &PWMD3, &PWM3cfg );
    pwmStart( &PWMD4, &PWM4cfg );
    pwmStart( &PWMD1, &PWM1cfg );

    while(true)
    {
        for (bright=0; bright<=10000; bright++)
        {
            pwmEnableChannel( &PWMD3, 2, bright );
            pwmEnableChannel( &PWMD4, 1, bright );
            pwmEnableChannel( &PWMD1, 1, bright );
            chThdSleepMilliseconds(5);
        }

        if (bright>=9500)
            {
                bright=0;
            }


    }
}
