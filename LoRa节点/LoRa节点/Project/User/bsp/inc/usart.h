#ifndef _USART_H_
#define _USART_H_


#include "stm32f10x.h"



////////////////////////////////
extern uint8_t rxd_flag;
extern char rxd_buf[100];
extern uint8_t rxd_index ;  //索引
///////////////////////////////
#define USART_DEBUG		USART1		//调试打印所使用的串口组
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART2_RX 			1		//使能（1）/禁止（0）串口1接收

extern uint32_t rxd_cnt;//接收计数变量

extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	




void Usart1_Init(unsigned int baud);

void Usart2_Init(unsigned int baud);

void Usart3_Init(unsigned int baud);

void lora_send_Byte(char Byte);

//void lanya_send_Byte(uint8_t Byte);
void lanya_send_Byte(char Byte);
	
void send_string(uint8_t *str);
	
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);


void lanya_send_buf(char *buf, uint16_t len);

void lora_send_buf(char *buf, uint16_t len);

void Lanya_Send_Pack(void);
	
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...);

void USART1_SendData(uint8_t *buf, uint8_t len);

void USART2_SendData(uint8_t *buf, uint8_t len);

void calculate_checksum(char *rxd_buf, uint32_t rxd_index);
	
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);

void Lora_SendAllInformation(void);
void Timer_SendBuf(void);


#endif


