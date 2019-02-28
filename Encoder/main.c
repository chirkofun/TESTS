#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include <enc.h>
#include <odometry.h>

/*
 * Serial 7 config
 */
static const SerialConfig UARTcfg = {
        .speed  = 9600,
        .cr1    = 0,
        .cr2    = 0,
        .cr3    = 0
    };

/*
 * Serial 7 Init
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
    EXT_Start();
    GPT_Init();

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
                                                     ticks, (int)turnover, (int)distance ,(int)speed);
        chThdSleepMilliseconds(100);

    }
}
