#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include <enc.h>
#include <ext.h>
#include <Serial_Init.h>


int main(void)
{
    chSysInit();
    halInit();
    sd7_init();

    EXT_Start();

    uint32_t ticks = 0;

    while(1)
    {
        ticks = get_ticks();
        chprintf(((BaseSequentialStream *)&SD7), "Ticks:(%d)\n\r", ticks);
        chThdSleepMilliseconds(50);
    }
}
