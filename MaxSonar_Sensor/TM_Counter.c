/*
 * TM_Counter.c
 *
 *  Created on: 20 февр. 2019 г.
 *      Author: cyirkofun
 */
#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include <stdint.h>

#define SYSTEM_FREQUENCY   216000000UL
static time_measurement_t  processing_time;
double result;

void TM_Counter_Init( void )
{
    chTMObjectInit( &processing_time );
}

void TM_Counter_Start (void)
{
    chTMStartMeasurementX( &processing_time );
}

double TM_Get_Time( void )
{
    float var;
    for( uint32_t g = 0; g < 400000; g++)
    {
        var = chVTGetSystemTimeX();
        var *= 2;
        var *= chVTGetSystemTimeX();
        var /= chVTGetSystemTimeX();
        var = var - 5.2;
    }

    return var;
}

void TM_Counter_Stop (void)
{
    chTMStopMeasurementX( &processing_time );
    chprintf( (BaseSequentialStream *)&SD7, "Best time:(%d)\tWorst time:(%d)\n\r",
                             RTC2US( SYSTEM_FREQUENCY, processing_time.best ),
                             RTC2US( SYSTEM_FREQUENCY, processing_time.worst ) );

}




