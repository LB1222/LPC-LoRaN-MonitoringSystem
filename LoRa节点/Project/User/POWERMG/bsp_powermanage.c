/*
*********************************************************************************************************
*
*	ģ������ : MCURCT��ʱ�������ģʽ
*	�ļ����� : bsp_powermanage.c
*	��    �� : V1.0
*	˵    �� :�ޡ�

*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2023-09-21  ����  ��ʽ����
*
*	
*
*********************************************************************************************************
*/
#include "bsp.h"

/************************************************************************************************
 * �� �� ��: RTC_Init
 * ��������: ����У���
 * ��������: uint8_t *buf ��Ҫ����У��͵Ŀ�ʼ�����ַ��uint8_t  len �����ۼӳ����ֽ�
 * �� �� ֵ: checkSum ������У���
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
		
		RTC_SetCounter(0);    //���ü�����ʼֵ
		
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



