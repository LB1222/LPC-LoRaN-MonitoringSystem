/*
*********************************************************************************************************
*
*	模块名称 : MCURCT定时进入待机模式
*	文件名称 : bsp_powermanage.c
*	版    本 : V1.0
*	说    明 :无。

*
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2023-09-21  刘斌  正式发布
*
*	
*
*********************************************************************************************************
*/
#include "bsp.h"

/************************************************************************************************
 * 函 数 名: RTC_Init
 * 函数功能: 计算校验和
 * 函数参数: uint8_t *buf 需要计算校验和的开始数组地址，uint8_t  len 计算累加长度字节
 * 返 回 值: checkSum 计算后的校验和
 ***********************************************************************************************/
void MyRTC_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	
	PWR_BackupAccessCmd(ENABLE);
	
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
	{
		RCC_LSEConfig(RCC_LSE_ON);
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET);
		
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);
		
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
		
		RTC_SetCounter(0);    //设置计数初始值
		
		RTC_SetPrescaler(32768 - 1);
		RTC_WaitForLastTask();
		
	//	MyRTC_SetTime();
		
		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
	}
	else
	{
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
	}
} 



