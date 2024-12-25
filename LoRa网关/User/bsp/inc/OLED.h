/*
*********************************************************************************************************
*
*	模块名称 : OLED指示灯驱动模块
*	文件名称 : bsp_oled.h
*	版    本 : V1.0
*	说    明 : 驱动oLED显示屏，模拟iic
*
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2023-07-19  刘斌  正式发布
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
