/**
	*	文件名： 	usart.c
	*
	*	作者： 		刘斌
	*
	*	日期： 		2023-11-23
	*
	*	版本： 		V1.0
	*
	*	说明： 		单片机串口外设初始化，格式化打印
	*
	*	修改记录：	
**/
#ifndef _USART_H_
#define _USART_H_


#include "stm32f10x.h"


#define USART_DEBUG		USART1		//调试打印所使用的串口组


void Usart1_Init(unsigned int baud);

void Usart2_Init(unsigned int baud);

void Usart3_Init(unsigned int baud);

void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);

void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...);

void lora_send_Byte(char Byte);

void lora_send_buf(char *buf, uint16_t len);

#endif
