/*
*********************************************************************************************************
*
*	ģ������ : LEDָʾ������ģ��
*	�ļ����� : bsp_led.h
*	��    �� : V1.0
*	˵    �� : ͷ�ļ�������½�����ʹ�ã��������ļ�
*
*	Copyright (C), 2014-2019, �����׵���
*
*********************************************************************************************************
*/

#ifndef __BSP_DATE_H
#define __BSP_DATE_H

#include "sys.h"


#define USART3_REC_LEN  			100  	//�����������ֽ��� 200
#define EN_USART3_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����



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

extern char volatile USART3_RX_BUF[USART3_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART3_RX_STA;         		//����״̬���	

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
extern char buffer_basisdate[80]; // ���ڴ洢��ʽ�����temp�ַ���
extern char buffer_alldate[80]; // ���ڴ洢��ʽ�����hum�ַ���
extern char buffer_dc[30]; // ���ڴ洢��ʽ�����dc�ַ���
extern char buffer_lt[30]; // ���ڴ洢��ʽ�����lt�ַ���
////////////////////
//////////////////////////
#define false 0
#define true 1

//�������鳤��
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
	char buffer_temp[temp_Length];		//�Ƿ��ȡ��GPS����
	char buffer_hum[hum_Length];		//�Ƿ��ȡ��GPS����
	char buffer_dc[dc_Length];		//�Ƿ��ȡ��GPS����
	char buffer_lt[lt_Length];		//�Ƿ��ȡ��GPS����
	char ChinaTime[ChinaTime_Length];		//UTCʱ��
	char latitude[latitude_Length];		//γ��
	char longitude[longitude_Length];		//����
	char altitude[altitude_Length]; //���θ߶�
	char isUsefull;		//��Ϣ�Ƿ���Ч
} _SaveData;



typedef union
{
    float f;
    uint8_t x[4];
} _sensorData; //���������� float �� 4 �ֽ� �໥�任 ʹ��������




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


