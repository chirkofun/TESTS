#include <stdint.h>
#include <ch.h>
#include <hal.h>



void Sort_Func (uint16_t *x, uint16_t window)
{
    uint16_t buff = 0;
    for (uint16_t i=0; i<(window-1); i++ )
    {
        for (uint16_t j=0; j<(window-i-1); j++)
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

uint16_t Filter_Mediana (uint16_t *x, uint16_t window)
{
    uint16_t z[window];
    uint16_t y;

    for (unsigned int k=0; k<window; k++)
    {
        z[k]=x[k];
    }
    Sort_Func(z, window);
    y = z[window/2];
    return(y);
}


