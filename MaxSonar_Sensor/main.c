#include <ch.h>
#include <hal.h>
#include <chprintf.h>
//#include <stdint.h>
#include <Filter_Mediana.h>
#include <Convert.h>
#include <Serial_Init.h>
#include <GPT_Counter.h>

int main(void)
{
    chSysInit();
    halInit();
    sd7_init();

    GPT_Counter_Init();

    float time = 0, delta;
    bool first = false;

    uint32_t value;
    static uint16_t window = 15;
    uint16_t rass[window], num, flt_num;

    while (true)
    {
        GPT_Counter_Start();
        if(first == false)
        {
            for (int i=0; i<window; i++)
            {
               value = sdGet(&SD7);
               if (value == 'R')
               {
                   sdRead(&SD7, (uint8_t *)&value , 3);
                   rass[i] = ASCIItoNUM(value, 3);
                   chThdSleepMilliseconds(30);
               }
               else
               {
                   i--;
               }

            }
            first = true;
        }


        value = sdGet(&SD7);
        if (value == 'R')
        {
            num = rass[window/2];
            flt_num = Filter_Mediana(rass, window);

            for (int i=0; i<window-1; i++)
            {
                rass[i] = rass[i+1];
            }

            sdRead(&SD7, (uint8_t *)&value , 3);
            rass[window-1] = ASCIItoNUM(value, 3);
            chThdSleepMilliseconds(30);
            delta = GPT_Get_Time() + 30;
            time += delta/1000;

//            chprintf(((BaseSequentialStream *)&SD7), "Time:(%d)\tNum:(%d)\tFlt:(%d)\n\r", (int)time, num, flt_num);
            sdWrite( &SD7, (uint8_t *)&time, sizeof(time));
            sdWrite( &SD7, (uint8_t *)&num, sizeof(num));
            sdWrite( &SD7, (uint8_t *)&flt_num, sizeof(flt_num));

        }
    }
}
