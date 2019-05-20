/*
 * GPT_Counter.c
 *
 *  Created on: 20 февр. 2019 г.
 *      Author: cyirkofun
 */


#include <GPT_Counter.h>

static void GPT_Counter_CB ( GPTDriver *GPT_Timer1);

static GPTDriver    *GPT_Timer1     = &GPTD1;

int32_t gpt_ticks       = 0;
int32_t total_time      = 0;

static const GPTConfig GPT1cfg = {
  .frequency =  100000,
  .callback  =  GPT_Counter_CB,
  .cr2       =  0,
  .dier      =  0U
};

#define TMR_TICKS_2_OVRFLOW   GPT1cfg.frequency/2


static void GPT_Counter_CB (GPTDriver *gptd)
{
    gptd = gptd;
    gpt_ticks += TMR_TICKS_2_OVRFLOW;
}

#define SYSTEM_FREQUENCY      GPT1cfg.frequency

void GPT_Counter_Init(void)
{
    gptStart(GPT_Timer1, &GPT1cfg);
}

void GPT_Counter_Start(void)
{
    gpt_ticks = 0;
    gptStartContinuous(GPT_Timer1, TMR_TICKS_2_OVRFLOW);
}

uint32_t GPT_Get_Time (void)
{
    total_time = gpt_ticks + gptGetCounterX(GPT_Timer1);
    uint32_t measure = (int)RTC2US( SYSTEM_FREQUENCY * 1.0, total_time );
    return(measure);
}
