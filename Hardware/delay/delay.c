#include "delay.h"

uint32_t fac_us;
uint16_t fac_ms;

void delayInit()
{
 	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  /* Disability SysTick counter */
}	

void delay_us(uint32_t nus){
  uint32_t temp = 0;
  uint64_t nms = 0;
  
  delayInit();
  if(nus == 0)
  {
    return;
  }
  nms = nus / 1000;
  nus = nus % 1000;
  
  if(nms > 0)
  {
    delay_ms(nms);
  }

  if(nus > 0)
  {
    SysTick->LOAD = SystemCoreClock / 8400000 * nus;  /* Time load (SysTick-> LOAD is 24bit) */
    SysTick->VAL = 0x000000;                          /* Empty counter */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;         /* Start the countdown */

    do
    {
      temp = SysTick->CTRL;
    }
    while(temp&0x01 && !(temp&(1<<16)));        /* Wait time is reached */

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  /* Close Counter */
    SysTick->VAL = 0x000000;                    /* Empty counter */
  }
}


void delay_ms(uint16_t nms){
  uint32_t temp = 0;
  
  delayInit();
  
  if(nms == 0)
  {
    return;
  }
  
  while(nms > 500)
  {
    SysTick->LOAD = SystemCoreClock / 84000 * 500; /* Time load (SysTick-> LOAD is 24bit) */
    SysTick->VAL = 0x000000;                      /* Empty counter */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;     /* Start the countdown */

    do
    {
      temp = SysTick->CTRL;
    }
    while(temp&0x01 && !(temp&(1<<16)));        /* Wait time is reached */

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  /* Close Counter */
    SysTick->VAL = 0x000000;                    /* Empty counter */
    
    nms -= 500;
  }
  
  SysTick->LOAD = SystemCoreClock / 14500 * nms; /* Time load (SysTick-> LOAD is 24bit) */
  SysTick->VAL = 0x000000;                      /* Empty counter */
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;     /* Start the countdown */

  do
  {
    temp = SysTick->CTRL;
  }
  while(temp&0x01 && !(temp&(1<<16)));        /* Wait time is reached */

  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  /* Close Counter */
  SysTick->VAL = 0x000000;                    /* Empty counter */
}