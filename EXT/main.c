#include <ch.h>
#include <hal.h>
#include <chprintf.h>

bool flag = FALSE;

static void EXT_CB( EXTDriver *extp, expchannel_t channel )
{
    extp = extp;
    channel = channel;

    for (unsigned int i=0; i<1000000; i++);
    bool k =  palReadPad(GPIOC, 13);
    if (k)
    {
        flag = !flag;
    }
}

static const EXTConfig EXTcfg = {
      .channels =
      {
        [0]  = {EXT_CH_MODE_DISABLED, NULL},
        [1]  = {EXT_CH_MODE_DISABLED, NULL},
        [2]  = {EXT_CH_MODE_DISABLED, NULL},
        [3]  = {EXT_CH_MODE_DISABLED, NULL},
        [4]  = {EXT_CH_MODE_DISABLED, NULL},
        [5]  = {EXT_CH_MODE_DISABLED, NULL},
        [6]  = {EXT_CH_MODE_DISABLED, NULL},
        [7]  = {EXT_CH_MODE_DISABLED, NULL},
        [8]  = {EXT_CH_MODE_DISABLED, NULL},
        [9]  = {EXT_CH_MODE_DISABLED, NULL},
        [10] = {EXT_CH_MODE_DISABLED, NULL},
        [11] = {EXT_CH_MODE_DISABLED, NULL},
        [12] = {EXT_CH_MODE_DISABLED, NULL},
        [13] = {EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC, EXT_CB}, //PC13 = Button
        [14] = {EXT_CH_MODE_DISABLED, NULL},
        [15] = {EXT_CH_MODE_DISABLED, NULL},
      }
    };



int main(void)
{
    chSysInit();
    halInit();

    extStart( &EXTD1, &EXTcfg );

    while (true)
       {
         if (flag)
         {
             palToggleLine(LINE_LED1);
             chThdSleepMilliseconds( 200 );
         }
         else
         {
             palClearLine(LINE_LED1);
         }
       }
}
