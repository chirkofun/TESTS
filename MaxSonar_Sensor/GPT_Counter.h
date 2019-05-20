/*
 * GPT_Counter.h
 *
 *  Created on: 20 февр. 2019 г.
 *      Author: cyirkofun
 */

#ifndef GPT_COUNTER_H_
#define GPT_COUNTER_H_

#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include <stdint.h>

void GPT_Counter_Init(void);
void GPT_Counter_Start(void);
uint32_t GPT_Get_Time (void);

#endif /* GPT_COUNTER_H_ */
