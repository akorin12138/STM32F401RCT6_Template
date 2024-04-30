#ifndef _UART_H
#define _UART_H

#include "stm32f4xx.h"
#include <stdio.h>


void UARTInit(uint32_t BAUDRATE);
void UART_SendByte(USART_TypeDef *USARTx, uint8_t data);
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);
int fputc(int ch, FILE *f);
int fgetc(FILE* f);
#define USER_MAIN_DEBUG
#ifdef USER_MAIN_DEBUG
#define user_main_printf(format, ...) printf(format "\r\n", ##__VA_ARGS__)
#define user_main_info(format, ...) printf("\t[main]info:" format "\r\n", ##__VA_ARGS__)
#define user_main_debug(format, ...) printf("\t[main]debug:" format "\r\n", ##__VA_ARGS__)
#define user_main_error(format, ...) printf("\t[main]error:" format "\r\n", ##__VA_ARGS__)
#else
#define user_main_printf(format, ...)
#define user_main_info(format, ...)
#define user_main_debug(format, ...)
#define user_main_error(format, ...)

#endif

#endif
