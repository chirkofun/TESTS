#include <ch.h>
#include <hal.h>
#include <chprintf.h>
//#include <stdint.h>
#include <Filter_Mediana.h>

void Sort_Func (uint32_t *x)
{
    uint16_t buff = 0;
    for (unsigned int i=1; i<sizeof(x); i++ )
    {
        for (uint16_t j=1; j<(sizeof(x)-i); j++)
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

uint32_t Filter_Mediana (uint32_t *x, uint16_t window)
{
    uint16_t w = window;
    uint32_t z[window];
    uint32_t y=0;

    *z = 0;
    for (unsigned int j=0; j<w; j++)
    {
        z[j]=x[j];
    }
    Sort_Func((uint32_t *)&z);
    y = z[w/2];

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

    uint16_t k = 100;
    uint16_t j = 0;

    uint32_t value;
    int16_t num = 0;

    uint16_t numbers[k];
    uint16_t rass[5];
    uint16_t window = 5;

    palSetPad(GPIOA, 3);
    palSetPad(GPIOC, 0);

//    uint16_t temp;
//    uint8_t temp1 =0;
//    uint8_t temp2 =0;
//    uint8_t temp3 =0;
//
//    for (int i=0; i<window; i++)
//    {
//
//        value = sdGet(&SD7);
//
//        if (value == 'R')
//        {
//            temp1 = sdGet( &SD7 );
//            temp2 = sdGet( &SD7 );
//            temp3 = sdGet( &SD7 );
//            temp = temp3 + (temp2<<8) + (temp1<<8);
//            temp = ASCIItoNUM(temp, 3);
//            sdReadTimeout(&SD7, (uint32_t *)&num, 3, TIME_IMMEDIATE);
//
//
//
//
//            chprintf(((BaseSequentialStream *)&SD7), "First:(%u)\tTemp1:(%u)\tTemp2:(%u)\tTemp3:(%u)\n\r",
//                     temp, temp1, temp2, temp3);
//            //num = ASCIItoNUM(num, 3);
//            sdWrite( &SD7, num, sizeof(num));
//        }
//        chThdSleepMilliseconds( 30 );
//
//    }




    while (true)
    {


//        numbers[j] = Filter_Mediana(&rass, window);
//
//        j++;
//
//
//
//        for (int i=0; i<window-1; i++)
//        {
//            rass[i] = rass [i+1];
//        }

        value = sdGet(&SD7);

        if (value == 'R')
        {
            sdRead(&SD7, (uint8_t *)&value , 3);
            num = ASCIItoNUM(value, 3);
            sdWrite( &SD7, (uint8_t *)&num, 2);
            chThdSleepMilliseconds(30);
        }



//        if(j==k)
//        {
//
//            j = 0;
//            //sdWrite( &SD7, &numbers, sizeof(numbers));
//        }


    }
}
