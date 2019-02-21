/*
 * ext.c
 *
 *  Created on: 21 февр. 2019 г.
 *      Author: cyirkofun
 */
#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include <stdint.h>

uint32_t enc_ticks = 0;

static void EXT_CB_A( EXTDriver *extp, expchannel_t channel )
{
    extp = extp;
    channel = channel;

    if(palReadPad(GPIOB, 4))
    {
        enc_ticks++;
    }
    else
    {
        enc_ticks--;
    }
}

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

void EXT_Start(void)
{
    extStart( &EXTD1, &EXTcfg );
}

uint32_t get_ticks(void)
{
    return(enc_ticks);
}

