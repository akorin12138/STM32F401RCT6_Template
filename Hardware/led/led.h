#ifndef _LED_H
#define _LED_H

#include "stm32f4xx.h"

#define ledon   GPIO_ResetBits(GPIOC,GPIO_Pin_7);
#define ledoff  GPIO_SetBits(GPIOC,GPIO_Pin_7);

void ledInit(void);

#endif
