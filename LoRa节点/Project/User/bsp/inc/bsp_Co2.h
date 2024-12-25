/*
*********************************************************************************************************
*
*	ģ������ : LEDָʾ������ģ��
*	�ļ����� : bsp_key.h
*	��    �� : V1.0
*	˵    �� : ����LEDָʾ�ƣ�����½�����ʹ�ã��������ļ�
*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2023.8.21  ����    keytest
*
*	
*
*********************************************************************************************************
*/
#ifndef __BSP_CO2_H
#define __BSP_CO2_H


extern float CO2_value;
extern char Co2ValueString[20];

#include"sys.h"

void ComparisonChecksum (void);
void Calculate_Co2Value(void);
void LowPower_Calculate_Co2Value(void);

#endif

