/*
 * odometry.c
 *
 *  Created on: 22 февр. 2019 г.
 *      Author: cyirkofun
 */
#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include <stdint.h>
#include <enc.h>

#define RADIUS 0.25
#define TRANSMITION_RATIO 1

float turnover = 0;
float prev_distance = 0, distance = 0, speed = 0;


float get_turnover(void)
{

    turnover = get_ticks();
    turnover /= 360;
    return(turnover);
}

float get_distance (void)
{
    distance = turnover*(2*3.1415*RADIUS)/TRANSMITION_RATIO;
    return(distance);
}

static void GPT_CB( GPTDriver *gptd )
{
    gptd = gptd;
    prev_distance = get_distance();
}

static GPTDriver    *GPT_Driver     = &GPTD1;

GPTConfig GPT1cfg = {
    .frequency    = 100000,
    .callback     = GPT_CB,
    .cr2          = 0,
    .dier         = 0
};

#define TMR_TICKS_2_OVRFLOW   GPT1cfg.frequency/100



void GPT_Init (void)
{
    gptStart( GPT_Driver, &GPT1cfg );
}

void GPT_Start (void)
{
    gptStartContinuous( GPT_Driver, TMR_TICKS_2_OVRFLOW );
}

float get_speed (void)
{
    float delta = 0;
    delta = distance - prev_distance;
    speed = delta*100;
    return(speed);
}

