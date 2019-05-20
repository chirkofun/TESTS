/*
 * sonar.h
 *
 *  Created on: 16 мая 2019 г.
 *      Author: cyirkofun
 */




#ifndef SONAR_H_
#define SONAR_H_

#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include <math.h>
#include <stdint.h>

/*
 * Serials UART Initialization for sonar sensors.
 */
void serial_init(void);

/*
 * @brief Bubble sorting function
 * @param x      - array
 *        window - size of array
 */
void Sort_Func (uint16_t *x, uint16_t window);

/*
 * @brief Choose medium value from array
 * @param x      - array
 *        window - size of array
 */
uint16_t Filter_Mediana (uint16_t *x, uint16_t window);

/*
 * @brief Bring distance from sonar sensor
 * @param   type_sonar  - selected sensor
 *          digits_num  - digits capacity (depending on type of sonar)
 *          window      - window for median filter
 */
uint16_t get_sonar_dist(SerialDriver *type_sonar, uint16_t digits_num, uint16_t window );


#endif /* SONAR_H_ */
