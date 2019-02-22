#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include <enc.h>
#include <odometry.h>

int main(void)
{
    chSysInit();
    halInit();
    sd7_init();
    EXT_Start();
    GPT_Init();

    GPT_Start();

    int32_t ticks = 0;
    float turnover = 0;
    float distance = 0, speed = 0;

    while(1)
    {
        ticks = get_ticks();
        turnover = get_turnover();
        distance = get_distance();
        speed = get_speed();

        chprintf(((BaseSequentialStream *)&SD7), "Ticks:(%d)\tTurnover:(%d)\tDistance:(%d)\tSpeed:(%d)\n\r",
                                                     ticks, (int)turnover, (int)distance, (int)speed);
        chThdSleepMilliseconds(50);

    }
}
