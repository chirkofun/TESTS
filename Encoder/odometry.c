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
#include <math.h>

/* Wheel radius */
#define RADIUS 0.25
/* Reducer transmition ratio  */
#define TRANSMITION_RATIO 1

/* Distance, Previous distance, changing the distance*/
float dist = 0, prev_dist = 0,  delta_dist = 0;

typedef float odometryDistanceValue_t;
typedef float odometrySpeedValue_t;

/*
 * @brief       Counts distance traveled (for certain wheel radius and transmition ratio)
 * @return      Distance in meters
 */
odometryDistanceValue_t get_distance (void)
{
    float distance = get_turnover()*(2*M_PI*RADIUS)/TRANSMITION_RATIO;
    return(distance);
}

/*
 * @brief       GPT Callback: counts previos distance and changing the distance
 */
static void GPT_CB( GPTDriver *gptd )
{
    gptd = gptd;
    prev_dist = dist;
    dist = get_distance();
    delta_dist = dist - prev_dist;
}

/* GPT1 driver assignment*/
static GPTDriver    *GPT_Driver     = &GPTD1;

/* GPT1 driver config*/
GPTConfig GPT1cfg = {
    .frequency    = 10000,
    .callback     = GPT_CB,
    .cr2          = 0,
    .dier         = 0
};

#define TMR_TICKS_2_OVRFLOW   (GPT1cfg.frequency/100)

/*
 * @brief       Odometry initialization and start
 */
void lld_Odometry_Init (void)
{
    gptStart( GPT_Driver, &GPT1cfg );
    gptStartContinuous( GPT_Driver, TMR_TICKS_2_OVRFLOW );
    lld_Encoder_Init();
}

/*
 * @brief       Counts moving speed: distance changing divides by time changing
 * @return      Speed in meters/seconds
 */
odometrySpeedValue_t get_speed (void)
{
    float delta_time = (float)GPT1cfg.frequency/(TMR_TICKS_2_OVRFLOW);
    float speed = delta_dist*delta_time;
    return(speed);
}

