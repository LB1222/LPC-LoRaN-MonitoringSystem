/*
*********************************************************************************************************
*
*	ģ������ : ���������
*	�ļ����� : main.c
*	��    �� : V1.0
*	˵    �� : LoRa�ڵ������ϱ��Լ���ʱ���ߡ�ʹ����systick�ж�ʵ�־�ȷ��ʱ��
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2024-04-02  ����  �׷�
*
*	
*
*********************************************************************************************************
*/

#include "stm32f10x.h"                  // Device header

#include "bsp.h"				/* �ײ�Ӳ������ */

//����

uint32_t Alarm;

	
		 
/*
*********************************************************************************************************
*	�� �� ��: main
*	����˵��: c�������
*	��    �Σ���
*	�� �� ֵ: �������(���账��)
*********************************************************************************************************
*/
int main(void)
{
  
/***********************************************************************88
		ST�̼����е������ļ��Ѿ�ִ���� SystemInit() �������ú����� system_stm32f10x.c �ļ�����Ҫ������
	����CPUϵͳ��ʱ��
*********************************************************8*/

	
	bsp_Idle();
	
	bsp_Init();		/* Ӳ����ʼ�� */
	
	Usart1_Init(9600);         //debug ����  ����  CO2
	Usart2_Init(9600);         //LORA
	Usart3_Init(9600);         //GPS
//	LANYA_SensorEN(); //����ʹ�� 
//	USART1_Lanya();   //����ʹ��
	USART1_Printf();
	printf("Beep On!\r\n");
	UsartPrintf(USART_DEBUG, " Hardware init OK !\r\n");
//	bsp_BeepOff();
//	delay_ms(100);
//  bsp_BeepOn();
 // Lora_TH_Display(); //����ʹ��
  //clrStruct();
	//USART1_Printf();
	//USART1_Lanya();
	 //USART1_CO2();
//	USART1_Lanya();
	USART2_LORA_EX_EN();
	//	GPS_EN_SensorEN();
	//	ADC_DC_EN_SensorEN();
	//	CO2_SensorEN();
	  //LANYA_SensorEN();
  //  Work_MDPin();  //����ʹ��
	//USART1_RESERVED();
	//�����͹���
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
//	
//	PWR_WakeUpPinCmd(ENABLE);
//	
//	 uint32_t Alarm = RTC_GetCounter() + 20;
//	RTC_SetAlarm(Alarm);

//�˳�ʼ���������������е��÷�


while(1)
	{
			
    
		bsp_LedOn(1);
		    delay_ms(1000);
		bsp_LedOff(1);
		//delay_ms(1000);
       
		
		delay_ms(1000);
		// UsartPrintf(USART2, " Hardware init OK !\r\n");
		//UsartPrintf(USART_DEBUG, " Hardware init OK !\r\n");
//	      Date_deal();
				

    }
}






