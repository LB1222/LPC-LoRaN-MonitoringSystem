/*
*********************************************************************************************************
*
*	ģ������ : OLEDָʾ������ģ��
*	�ļ����� : bsp_oled.h
*	��    �� : V1.0
*	˵    �� : ����oLED��ʾ����ģ��iic
*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2023-07-19  ����  ��ʽ����
*
*	
*
*********************************************************************************************************
*/

#ifndef __OLED_H
#define __OLED_H


#include "sys.h"
void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_Write_Display(uint8_t x,uint8_t y,uint8_t g,uint8_t k,uint8_t *dat);
void OLED_Write_Number(uint8_t x, uint8_t y, uint8_t Num);
void Lora_TH_Display(void);
#endif
