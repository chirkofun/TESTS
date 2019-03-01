/*
 * enc.c
 *
 *  Created on: 21 февр. 2019 г.
 *      Author: cyirkofun
 */
#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include <stdint.h>

/*Encoder channel A*/
#define ENC_CH_A PAL_LINE( GPIOB , 5 )

/*Encoder channel B*/
#define ENC_CH_B PAL_LINE( GPIOB , 4 )

/*Encoder maximum number of ticks*/
#define ENC_MAX_TICK 360

/* Encoder tick count, global value*/
int32_t enc_ticks = 0;

typedef int32_t encoderTicksValue_t;
typedef float encoderTurnoverValue_t;

/*
 * @brief       Counts encoder ticks
 * @param [in]  EXT driver, EXT channel
 */
static void EXT_CB_A( EXTDriver *extp, expchannel_t channel )
{
    extp = extp;
    channel = channel;

    if(palReadLine(ENC_CH_B))
    {
        enc_ticks++;
    }
    else
    {
        enc_ticks--;
    }
}

/* EXT config, reading from 5 channel (PORT B) */
static const EXTConfig EXTcfg = {
      .channels =
      {
        [0]  = {EXT_CH_MODE_DISABLED, NULL},
        [1]  = {EXT_CH_MODE_DISABLED, NULL},
        [2]  = {EXT_CH_MODE_DISABLED, NULL},
        [3]  = {EXT_CH_MODE_DISABLED, NULL},
        [4]  = {EXT_CH_MODE_DISABLED, NULL},
        [5]  = {EXT_CH_MODE_FALLING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOB, EXT_CB_A}, //pb5 - Channel A
        [6]  = {EXT_CH_MODE_DISABLED, NULL},
        [7]  = {EXT_CH_MODE_DISABLED, NULL},
        [8]  = {EXT_CH_MODE_DISABLED, NULL},
        [9]  = {EXT_CH_MODE_DISABLED, NULL},
        [10] = {EXT_CH_MODE_DISABLED, NULL},
        [11] = {EXT_CH_MODE_DISABLED, NULL},
        [12] = {EXT_CH_MODE_DISABLED, NULL},
        [13] = {EXT_CH_MODE_DISABLED, NULL},
        [14] = {EXT_CH_MODE_DISABLED, NULL},
        [15] = {EXT_CH_MODE_DISABLED, NULL},
      }
    };

/*
 * @brief       Starts EXT module
 */
void lld_Encoder_Init(void)
{
    extStart( &EXTD1, &EXTcfg );
}

/*
 * @brief       Return encoder ticks
 * @return      Encoder ticks
 */
encoderTicksValue_t get_ticks(void)
{
    return(enc_ticks);
}

/*
 * @brief       Counts encoder turnovers
 * @return      Number of turnovers
 */
encoderTurnoverValue_t get_turnover(void)
{
    return((float)enc_ticks/ENC_MAX_TICK);
}






