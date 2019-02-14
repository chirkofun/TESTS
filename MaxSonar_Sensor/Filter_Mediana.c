#include <stdint.h>
#include <ch.h>
#include <hal.h>

void Sort_Func (uint32_t *x)
{
    uint16_t buff = 0;
    for (unsigned int i=1; i<sizeof(x); i++ )
    {
        for (uint16_t j=1; j<(sizeof(x)-i); j++)
        {
            if (x[j]<x[j+1])
            {
                buff = x[j];
                x[j] = x[j + 1];
                x[j + 1] = buff;
            }
        }
    }
}

uint32_t Filter_Mediana (uint32_t *x, uint16_t window)
{
    uint16_t w = window;
    uint32_t z[window];
    uint32_t y=0;

    *z = 0;
    for (unsigned int j=0; j<w; j++)
    {
        z[j]=x[j];
    }
    Sort_Func(*z);
    y = z[w/2];

    return(y);
}

