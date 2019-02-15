#include <ch.h>
#include <hal.h>
#include <chprintf.h>
//#include <stdint.h>
#include <Filter_Mediana.h>

void Sort_Func (uint16_t *x)
{
    uint16_t buff = 0;
    for (unsigned int i=0; i<sizeof(x)-1; i++ )
    {
        for (uint16_t j=0; j<(sizeof(x)-i-1); j++)
        {
            if (x[j]<x[j+1])
            {
                buff = x[j];
                x[j] = x[j + 1];
                x[j + 1] = buff;
            }
        }
    }
}

uint16_t Filter_Mediana (uint16_t *x, uint16_t window)
{
    uint16_t z[window];
    uint16_t y;

    for (unsigned int k=0; k<window; k++)
    {
        z[k]=x[k];
    }
    Sort_Func(z);
    y = z[window/2+1];
    return(y);
}

/*
 * Serial UART configuration.
 */
static const SerialConfig UARTcfg = {
        .speed  = 9600,
        .cr1    = 0,
        .cr2    = 0,
        .cr3    = 0
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

unsigned int ASCIItoNUM(uint32_t num, unsigned char m)
{
    unsigned int res = 0;
    for(unsigned char i=0; i<m; i++)
    {
        unsigned int buff = num;
        unsigned int exp = 1;
        buff = (uint32_t)(buff >> (8*i));
        buff = (uint32_t)(buff << (8*m));
        buff = (uint32_t)(buff >> (8*m));
        for(unsigned char j=(m-1)-i;j>0;j--)
        {
            exp *= 10;
        }
        res = res + (buff-48)*exp;
    }
    return(res);
}

int main(void)
{
    chSysInit();
    halInit();
    sd7_init();

    float time = 0;
    bool first = false;

    uint32_t value;
    uint16_t flt_num, num;
    uint16_t window = 5;
    uint16_t rass[window];

    palSetPad(GPIOA, 3);
    palSetPad(GPIOC, 0);

    while (true)
    {
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
                   time = time + 0.03;
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
            num = rass[window/2+1];
            flt_num = Filter_Mediana(rass, window);

            for (int i=0; i<window-1; i++)
            {
                rass[i] = rass[i+1];
            }

            sdRead(&SD7, (uint8_t *)&value , 3);
            rass[window-1] = ASCIItoNUM(value, 3);
            chThdSleepMilliseconds(30);
            time = time + 0.03;

//            chprintf(((BaseSequentialStream *)&SD7), "Time:(%d)\tNum:(%d)\tFlt:(%d)\n\r", (int)time, num, flt_num);
            sdWrite( &SD7, (uint8_t *)&time, sizeof(time));
            sdWrite( &SD7, (uint8_t *)&num, sizeof(num));
            sdWrite( &SD7, (uint8_t *)&flt_num, sizeof(flt_num));
        }

    }
}
