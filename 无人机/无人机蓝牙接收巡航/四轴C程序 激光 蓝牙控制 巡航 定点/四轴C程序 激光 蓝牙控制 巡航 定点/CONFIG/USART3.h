//#ifndef __USART_H
//#define __USART_H
//#include "stdio.h"	
//#include "sys.h" 
//#define USART_REC_LEN  			200  	//�����������ֽ��� 200
//#define EN_USART3_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
//	  	
//extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
//extern u16 USART_RX_STA;         		//����״̬���	


//extern uint8_t rxd_flag ;
//void uart1_init(u32 bound);
//void Send_Pack(void);
//void USART3_Config(u32 br_num);
//#endif

#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>


extern void USART3_SendByte(const int8_t *Data,uint8_t len);

extern void USART3_Config(u32 br_num);
void ANO_UART3_DeInit(void);
void ANO_UART3_IRQ(void);

void USART3_Send1(const int8_t Data);

extern uint8_t rxd_flag ;
extern uint8_t mode_flag ;
void Send_Pack(void);

extern void USART1_setBaudRate(uint32_t baudRate);

#endif /* __USART1_H */

