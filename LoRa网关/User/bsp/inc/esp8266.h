/**
	*	文件名： 	esp8266.h
	*
	*	作者： 		刘斌
	*
	*	日期： 		2024-01-08
	*
	*	版本： 		V1.0
	*
	*	说明： 		ESP8266的简单驱动
	*
	*	修改记录：	
**/
#ifndef _ESP8266_H_
#define _ESP8266_H_





#define REV_OK		0	//接收完成标志
#define REV_WAIT	1	//接收未完成标志


void ESP8266_Init(void);

void ESP8266_Clear(void);

void ESP8266_SendData(unsigned char *data, unsigned short len);

unsigned char *ESP8266_GetIPD(unsigned short timeOut);


#endif
