/*
 * enc.h
 *
 *  Created on: 21 ����. 2019 �.
 *      Author: cyirkofun
 */

#ifndef ENC_H_
#define ENC_H_

#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include <odometry.h>
#include <math.h>
#include <stdint.h>

/* Encoder tick count, global value*/
int32_t enc_ticks = 0;

typedef int32_t encoderTicksValue_t;
typedef float encoderTurnoverValue_t;

/*
 * @brief       Starts EXT module
 */
void lld_Encoder_Init(void);

/*
 * @brief       Return encoder ticks
 * @return      Encoder ticks
 */
encoderTicksValue_t get_ticks(void);

/*
 * @brief       Counts encoder turnovers
 * @return      Number of turnovers
 */
encoderTurnoverValue_t get_turnover(void);


#endif /* ENC_H_ */
