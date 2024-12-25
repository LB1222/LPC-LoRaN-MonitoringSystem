/*
*********************************************************************************************************
*
*	模块名称 : 主程序入口
*	文件名称 : main.c
*	版    本 : V1.0
*	说    明 : LoRa节点数据上报以及定时休眠。使用了systick中断实现精确定时。
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2024-04-02  刘斌  首发
*
*	
*
*********************************************************************************************************
*/

#include "stm32f10x.h"                  // Device header

#include "bsp.h"				/* 底层硬件驱动 */

//声明

uint32_t Alarm;

	
		 
/*
*********************************************************************************************************
*	函 数 名: main
*	功能说明: c程序入口
*	形    参：无
*	返 回 值: 错误代码(无需处理)
*********************************************************************************************************
*/
int main(void)
{
  
/***********************************************************************88
		ST固件库中的启动文件已经执行了 SystemInit() 函数，该函数在 system_stm32f10x.c 文件，主要功能是
	配置CPU系统的时钟
*********************************************************8*/

	
	bsp_Idle();
	
	bsp_Init();		/* 硬件初始化 */
	
	Usart1_Init(9600);         //debug 串口  蓝牙  CO2
	Usart2_Init(9600);         //LORA
	Usart3_Init(9600);         //GPS
//	LANYA_SensorEN(); //测试使用 
//	USART1_Lanya();   //测试使用
	USART1_Printf();
	printf("Beep On!\r\n");
	UsartPrintf(USART_DEBUG, " Hardware init OK !\r\n");
//	bsp_BeepOff();
//	delay_ms(100);
//  bsp_BeepOn();
 // Lora_TH_Display(); //测试使用
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
  //  Work_MDPin();  //测试使用
	//USART1_RESERVED();
	//开启低功耗
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
//	
//	PWR_WakeUpPinCmd(ENABLE);
//	
//	 uint32_t Alarm = RTC_GetCounter() + 20;
//	RTC_SetAlarm(Alarm);

//此初始化函数在主函数中的用法


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






