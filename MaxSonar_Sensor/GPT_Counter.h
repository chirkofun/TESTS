/*
 * GPT_Counter.h
 *
 *  Created on: 20 февр. 2019 г.
 *      Author: cyirkofun
 */

#ifndef GPT_COUNTER_H_
#define GPT_COUNTER_H_

static void GPT_Counter_CB (GPTDriver *GPT_Timer1 );
void GPT_Counter_Init(void);
void GPT_Counter_Start(void);
void GPT_Get_Time (void);


#endif /* GPT_COUNTER_H_ */
