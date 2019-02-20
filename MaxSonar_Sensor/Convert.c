/*
 * Convert.c
 *
 *  Created on: 20 февр. 2019 г.
 *      Author: cyirkofun
 */

#include <stdint.h>
#include <ch.h>
#include <hal.h>

unsigned int ASCIItoNUM(uint32_t num, unsigned char m)
{
    unsigned int res = 0;
    for(unsigned char i=0; i<m; i++)
    {
        unsigned int buff = num;
        unsigned int exp = 1;
        buff = (uint32_t)(buff >> (8*i));
        buff = (uint32_t)(buff << (8*m));
        buff = (uint32_t)(buff >> (8*m));
        for(unsigned char j=(m-1)-i;j>0;j--)
        {
            exp *= 10;
        }
        res = res + (buff-48)*exp;
    }
    return(res);
}

