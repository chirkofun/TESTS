#ifndef FILTER_MEDIANA_H_
#define FILTER_MEDIANA_H_

#include <stdint.h>
#include <ch.h>
#include <hal.h>


void Sort_Func (uint16_t* x);
uint16_t Filter_Mediana(uint16_t *x, uint16_t window);

#endif