#include "uart.h"

void NVIC_Config_UART(void)//NVIC：中断
{
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//4位数字 0 0 0 0存放主子优先级模式设定
    NVIC_Init(&NVIC_InitStruct);
}

void UARTInit(uint32_t BAUDRATE)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); // 使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE); // 使能串口1时钟
	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); // 将PA9复用成串口1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);// 将PA10复用成串口1
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; // GPIO引脚模式为复用模式
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct); // 初始化GPIO
	
	USART_InitStruct.USART_BaudRate = BAUDRATE; // 波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用流控
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // 串口模式为发送和接收模式
	USART_InitStruct.USART_Parity = USART_Parity_No; // 不校验
	USART_InitStruct.USART_StopBits = USART_StopBits_1; // 一位停止位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; // 8位数据位
	USART_Init(USART1,&USART_InitStruct); // 初始化串口
	USART_Cmd(USART1,ENABLE); // 使能串口
}



void UART_SendByte(USART_TypeDef* USARTx,uint8_t data)
{
    USART_SendData(USARTx,data);
    while(!USART_GetFlagStatus(USARTx,USART_FLAG_TXE));//若寄存器有数据则为空，此时USART_GetFlagStatus返回1，有数据时为0
}

void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len)
{

	unsigned short count = 0;
	
	for(; count < len; count++)
	{
		USART_SendData(USARTx, *str++);								
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);	
	}

}


//==============================收发串口数据方式2————stdio重定向===================================
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}
int fgetc(FILE* f)
{
    while(!USART_GetFlagStatus(USART1,USART_FLAG_RXNE));//没有数据的时候等待，有数据的时候跳出循环
    return (int)USART_ReceiveData(USART1);
}
