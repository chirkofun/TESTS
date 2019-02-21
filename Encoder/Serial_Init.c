/*
 * Serial_Init.c
 *
 *  Created on: 20 февр. 2019 г.
 *      Author: cyirkofun
 */

#include <stdint.h>
#include <ch.h>
#include <hal.h>

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
