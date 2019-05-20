/*
 * sonar.c

 *
 *  Created on: 16 ��� 2019 �.
 *      Author: cyirkofun
 */
#include <sonar.h>

//Serial 7 TX and RX ports
#define frontLeftSonarTX        PAL_LINE( GPIOE, 8 )
#define frontLeftSonarRX        PAL_LINE( GPIOE, 7 )

//Serial 6 TX and RX ports
#define leftSonarTX             PAL_LINE( GPIOC, 6 )
#define leftSonarRX             PAL_LINE( GPIOC, 7 )

//Serial 7 TX and RX ports
#define backLeftSonarTX         PAL_LINE( GPIOB, 13 )
#define backLeftSonarRX         PAL_LINE( GPIOB, 12 )

SerialDriver *frontLeftSonar =  &SD7;
SerialDriver *leftSonar      =  &SD6;
SerialDriver *backLeftSonar  =  &SD5;

bool firstValues = false;

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
 * Serials UART Initialization for sonar sensors.
 */
void serial_init(void)
{
    sdStart( frontLeftSonar, &UARTcfg );
    sdStart( leftSonar     , &UARTcfg );
    sdStart( backLeftSonar , &UARTcfg );

    palSetLineMode( frontLeftSonarTX, PAL_MODE_ALTERNATE(8) );      // TX for front left sensor
    palSetLineMode( frontLeftSonarRX, PAL_MODE_ALTERNATE(8) );      // RX for front left sensor
    palSetLineMode( leftSonarTX, PAL_MODE_ALTERNATE(8) );           // TX for left sensor
    palSetLineMode( leftSonarRX, PAL_MODE_ALTERNATE(8) );           // RX for left sensor
    palSetLineMode( backLeftSonarTX, PAL_MODE_ALTERNATE(8) );       // TX for back left sensor
    palSetLineMode( backLeftSonarRX, PAL_MODE_ALTERNATE(8) );       // RX for back left sensor

    palSetPad(GPIOF, 4); //High level pin 4 for Sonar front left
    palSetPad(GPIOF, 5); //High level pin 4 for Sonar left
    palSetPad(GPIOC, 4); //High level pin 4 for Sonar back left
}

/*
 * @brief Bubble sorting function
 * @param x      - array
 *        window - size of array
 */
void Sort_Func (uint16_t *x, uint16_t window)
{
    uint16_t buff = 0;
    for (uint16_t i=0; i<(window-1); i++ )
    {
        for (uint16_t j=0; j<(window-i-1); j++)
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

/*
 * @brief Choose medium value from array
 * @param x      - array
 *        window - size of array
 */
uint16_t Filter_Mediana (uint16_t *x, uint16_t window)
{
    uint16_t z[window];
    uint16_t y;

    for (unsigned int k=0; k<window; k++)
    {
        z[k]=x[k];
    }
    Sort_Func(z, window);
    y = z[window/2];
    return(y);
}

/*
 * @brief Bring distance from sonar sensor
 * @param   type_sonar  - selected sensor
 *          digits_num  - digits capacity (depending on type of sonar)
 *          window      - window for median filter
 */
uint16_t get_sonar_dist(SerialDriver *type_sonar, uint16_t digits_num, uint16_t window )
{
    uint32_t value = 0;
    uint16_t filterWindow[window], num, flt_num = 0;

    if(firstValues == false)
    {
        for (int i=0; i<window; i++)
        {
            value = sdGet(type_sonar);
            if (value == 'R')
            {
                sdRead(type_sonar, (uint8_t *)&value , digits_num);
                filterWindow[i] = atoi(&value);
                chThdSleepMilliseconds(30);

            }
            else
            {
                i--;
            }
        }
        firstValues = true;
    }

    if(firstValues == true)
    {
        value = sdGet(type_sonar);
        if (value == 'R')
        {
            num = filterWindow[window/2];
            flt_num = Filter_Mediana(filterWindow, window);
            for (int i=0; i<window-1; i++)
            {
                filterWindow[i] = filterWindow[i+1];
            }
            sdRead(type_sonar, (uint8_t *)&value , digits_num);
            filterWindow[window-1] = atoi(&value);
            chThdSleepMilliseconds(30);

            return(flt_num);
        }
    }

}