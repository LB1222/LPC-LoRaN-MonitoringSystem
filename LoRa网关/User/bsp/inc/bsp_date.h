/*
*********************************************************************************************************
*
*	模块名称 : LED指示灯驱动模块
*	文件名称 : bsp_led.h
*	版    本 : V1.0
*	说    明 : 头文件，配合新建工程使用，非完整文件
*
*	Copyright (C), 2014-2019, 德致伦电子
*
*********************************************************************************************************
*/

#ifndef __BSP_DATE_H
#define __BSP_DATE_H

#include "sys.h"


#define USART3_REC_LEN  			100  	//定义最大接收字节数 200
#define EN_USART3_RX 			1		//使能（1）/禁止（0）串口1接收



//////////////////
#define FRAME_HEADER1 0x4C
#define FRAME_HEADER2 0x30
#define FRAME_HEADER3 0x31
#define FRAME_HEADER_ALT1 0x53
#define FRAME_HEADER_ALT2 0x30
#define FRAME_HEADER_ALT3 0x31
#define FRAME_TAIL1 0x11
#define FRAME_TAIL2 0x11
#define FRAME_TAIL3 0x11
#define MAX_DATA_LENGTH1 55
#define MAX_DATA_LENGTH2 55

////////////////////////



extern volatile uint8_t Lora_rxd_flag;

extern char volatile USART3_RX_BUF[USART3_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART3_RX_STA;         		//接收状态标记	

//////////
extern volatile uint8_t rxBuffer[MAX_DATA_LENGTH1];
//////////

//////////////////
extern float Temp_value;
extern float Hum_value;
extern float LT_value;
extern float CO2_value;
extern float DC_value;
extern float TIME_value;
extern float latitude_value;
extern float longitude_value;
extern float altitude_value;

///////////////////
extern char buffer_basisdate[80]; // 用于存储格式化后的temp字符串
extern char buffer_alldate[80]; // 用于存储格式化后的hum字符串
extern char buffer_dc[30]; // 用于存储格式化后的dc字符串
extern char buffer_lt[30]; // 用于存储格式化后的lt字符串
////////////////////
//////////////////////////
#define false 0
#define true 1

//定义数组长度
#define LORA1_BasisBuffer_Length 50
#define LORA1_AllBuffer_Length 50
#define LORA2_Buffer_Length 100
#define LORA3_Buffer_Length 100
#define temp_Length 30
#define hum_Length 30
#define CO2_Length 30
#define dc_Length 30
#define lt_Length 30
#define ChinaTime_Length 30
#define latitude_Length 30
#define longitude_Length 30
#define altitude_Length 30 


typedef struct SaveData 
{
	char LORA1_BasisBuffer[LORA1_BasisBuffer_Length];
  char LORA1_AllBuffer[LORA1_AllBuffer_Length];
	
	char LORA2_Buffer[LORA2_Buffer_Length];
	char LORA3_Buffer[LORA3_Buffer_Length];
	char buffer_temp[temp_Length];		//是否获取到GPS数据
	char buffer_hum[hum_Length];		//是否获取到GPS数据
	char buffer_dc[dc_Length];		//是否获取到GPS数据
	char buffer_lt[lt_Length];		//是否获取到GPS数据
	char ChinaTime[ChinaTime_Length];		//UTC时间
	char latitude[latitude_Length];		//纬度
	char longitude[longitude_Length];		//经度
	char altitude[altitude_Length]; //海拔高度
	char isUsefull;		//信息是否有效
} _SaveData;



typedef union
{
    float f;
    uint8_t x[4];
} _sensorData; //传感器数据 float 与 4 字节 相互变换 使用联合体




typedef enum {
    IDLE_STATE,
    HEADER1_STATE,
    HEADER2_STATE,
    HEADER3_STATE,
	  HEADER_ALT1_STATE,
    HEADER_ALT2_STATE,
    HEADER_ALT3_STATE,
    DATA_STATE,
    TAIL1_STATE,
    TAIL2_STATE,
    TAIL3_STATE
} ReceiveState;



extern char rxdatabufer;
extern u16 point1;
extern _SaveData Save_Data;

void BasisDate_Analysis(void);
void AllDate_Analysis(void);
void clrStruct(void);
void DateuploadEMQX(void);


void test_Analysis(void);
	

#endif


