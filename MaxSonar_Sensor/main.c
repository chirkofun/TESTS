#include <stdlib.h>
#include <GPT_Counter.h>
#include <sonar.h>

int main(void)
{
    chSysInit();
    halInit();
    serial_init();

    GPT_Counter_Init();

    float time = 0, delta;
    uint16_t filteredValue;

    while (true)
    {
        GPT_Counter_Start();
        filteredValue = get_sonar_dist(&SD6, 4, 10);
        chThdSleepMilliseconds(30);
        delta = GPT_Get_Time() + 30;
        time += delta/1000;

        chprintf(((BaseSequentialStream *)&SD6), "Time:(%d)\tFlt:(%d)\n\r", (int)time, filteredValue);
//            sdWrite( &SD6, (uint8_t *)&time, sizeof(time));
//            sdWrite( &SD6, (uint8_t *)&filteredValue, sizeof(filteredValue));


    }
}
