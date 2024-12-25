/*
*********************************************************************************************************
*
*	模块名称 : LED指示灯驱动模块
*	文件名称 : bsp_key.h
*	版    本 : V1.0
*	说    明 : 驱动LED指示灯，配合新建工程使用，非完整文件
*
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2023.8.21  刘斌    keytest
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

