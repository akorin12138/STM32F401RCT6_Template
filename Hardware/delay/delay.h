#ifndef _DELAY_H
#define _DELAY_H


#include "stm32f4xx.h"

void delayInit(void);
void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);

#endif
