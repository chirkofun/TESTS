#include <ch.h>
#include <hal.h>
#include <chprintf.h>

static const DACConfig DAC1cfg = {
  .init         = 0,
  .datamode     = DAC_DHRM_12BIT_RIGHT,
  .cr           = 0
};

int main(void)
{
    chSysInit();
    halInit();

    palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_ANALOG);  // PA4


    dacStart(&DACD1, &DAC1cfg);  //DAC driver start

    dacPutChannelX( &DACD1 , 0 , 4000 );

    while (true)
       {
            palClearPad(GPIOA, 4);
            chThdSleepMilliseconds(30);
       }
}
