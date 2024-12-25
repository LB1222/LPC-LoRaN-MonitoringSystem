/*
*********************************************************************************************************
*
*	模块名称 : ADC采样光敏电阻值及电池电压
*	文件名称 : bsp_adc.c
*	版    本 : V1.0
*	说    明 : wu
*
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2023-04-19  刘斌  正式发布
*
*	
*
*********************************************************************************************************
*/
#include "bsp.h"

uint16_t ADC_ConvertedValue[2]; // 存储ADC数据的缓冲区，每个通道一个元素



//__IO uint16_t ADC_ConvertedValue; //light 值
float ADC_ConvertedValueLocal;        
char Dis_AD_VO_Buf[20]={0};
char Dis_VA_Buf[20]={0};
//volatile uint8_t samplingVoltage = 1; // 初始状态下采样电压
 //uint16_t  adcValueLight;
/////////////////////////////////////转发得BUF
char DC_Buf[20];
char LT_Buf[20];
float DC_value;
float DC_alarm_value;
float LT_value;
float LT_alarm_value;

/////////////////////////////////////

/**
  * @brief  ADC GPIO 初始化
  * @param  无
  * @retval 无
  */
#include "stm32f10x.h"

void GPIO_Configuration(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    // 启用GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 配置PA5和PA6为模拟输入模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void ADC_Configuration(void) {
    // 启用ADC1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    // 初始化ADC结构体
    ADC_InitTypeDef ADC_InitStructure;
	  DMA_InitTypeDef DMA_InitStructure;
    ADC_StructInit(&ADC_InitStructure);

    // 配置ADC参数
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; // 独立模式
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;      // 禁用扫描模式
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; // 连续转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 不使用外部触发
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // 数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 2; // 同时采样一个通道

    ADC_Init(ADC1, &ADC_InitStructure);

    // 配置ADC通道
    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_239Cycles5); // 配置通道5（PA5）
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 2, ADC_SampleTime_239Cycles5); // 配置通道6（PA6）

    // 启用ADC1
   ADC_DMACmd(ADC1, ENABLE);

    // 启用ADC1转换
   // ADC_Cmd(ADC1, ENABLE);
		
		 // 配置DMA时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    // 配置DMA参数
		DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvertedValue;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = 2; // 采样两个数据
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; // 循环模式，持续采样
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

    DMA_Init(DMA1_Channel1, &DMA_InitStructure);

    // 启动DMA
    DMA_Cmd(DMA1_Channel1, ENABLE);

    // 启用ADC1
    ADC_Cmd(ADC1, ENABLE);

    // 启动ADC1校准
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));

    // 启动ADC1转换
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
		 DMA_ClearFlag(DMA1_FLAG_TC1);
}




void Get_battery_volt(void)   
{  
	  
		uint16_t DA_ROnce=0,DC_ALLValue=0;
		uint16_t StandradDCValue = 370.0;
		float  percentage=0 ;
		uint16_t DC_FinalValue=0;//电压值
		uint8_t i;
	  uint16_t adcValueVoltage=0;     
    adcValueVoltage = ADC_ConvertedValue[1];   // 通道6（PA6）的采样值
	  for(i=0;i<100;i++)
		{
		DA_ROnce=adcValueVoltage*3.3*11*100/4096;//电阻分压，电池电压读取计算公式
		DC_ALLValue+=DA_ROnce;
		}
	  
    DC_FinalValue=DC_ALLValue/100;
		
		percentage = ((float)DC_FinalValue/StandradDCValue)*100.0;
		printf("DCValue: %.2f%%\r\n",percentage);
		DC_value = percentage;
		//sensor_DC_Upload(DC_value);
		if(percentage<20)
		{
			DC_alarm_value = percentage;
			//sensor_DC_Upload(DC_alarm_value);
		}
		//sprintf(DC_Buf,"DCValue: %.2f%%\r\n",percentage);
	//	printf("%f\r\n",percentage);
		printf("adcDC:%d\r\n",adcValueVoltage);
		
}


void Get_Light_value(void)
{
	uint16_t  adcValueLight=0;	
	float Lightpercentage=0 ;
	uint16_t i,LT_ROnce=0,LT_ALLValue=0;
	  adcValueLight = ADC_ConvertedValue[0]; // 通道5（PA5）的采样值
		// 读取ADC的转换值
		LT_ROnce =  adcValueLight;
	ADC_ConvertedValueLocal =(float)adcValueLight*3.3/4096; 
		delay_ms(1000);
	 for(i=0;i<100;i++)
	{
		LT_ALLValue+=LT_ROnce;
	}
	
	LT_ALLValue = LT_ALLValue/100.0;
	///////////////////////////////////
	printf("adcLT:%d\r\n",adcValueLight); 
//	///////////////////////////////////
//	printf("  AD_VO:%.4fV \r\n",ADC_ConvertedValueLocal);
//	sprintf(DC_Buf,"  AD_VO:%.4fV",ADC_ConvertedValueLocal);
	
	if(LT_ALLValue>3000)
	{
		int NormalValue = 3000;
		LT_ALLValue=3000;
		Lightpercentage=(float)LT_ALLValue/NormalValue*100.0;
		Lightpercentage=(Lightpercentage-100);
		LT_value = Lightpercentage;
		//sensor_Luminance_Upload(LT_value);
		printf("LightValue: %.2f%%\r\n",Lightpercentage);
	}
	else if(LT_ALLValue>2000&&LT_ALLValue<3000)
	{
		int NormalValue = 3000;
		Lightpercentage=(float)LT_ALLValue/NormalValue*100.0;
		Lightpercentage=(Lightpercentage-100);
		Lightpercentage=-Lightpercentage;
		LT_value = Lightpercentage;
		//sensor_Luminance_Upload(LT_value);
		printf("LightValue: %.2f%%\r\n",Lightpercentage);
		sprintf(LT_Buf,"LightValue: %.2f%%",Lightpercentage);
	}
	else if(LT_ALLValue>1000&&LT_ALLValue<2000)
	{
		int NormalValue = 2000;
		Lightpercentage=(float)LT_ALLValue/NormalValue*100.0;
		Lightpercentage=(Lightpercentage-100);
		Lightpercentage=-Lightpercentage;
		LT_value = Lightpercentage;
		//sensor_Luminance_Upload(LT_value);
		printf("LightValue: %.2f%%\r\n",Lightpercentage);
		sprintf(LT_Buf,"LightValue: %.2f%%",Lightpercentage);
	}
		else if(LT_ALLValue>100&&LT_ALLValue<1000)
	{
		int NormalValue = 1000;
		Lightpercentage=(float)LT_ALLValue/NormalValue*100.0;
		Lightpercentage=(Lightpercentage-100);
		Lightpercentage=-Lightpercentage;
		printf("LightValue: %.2f%%\r\n",Lightpercentage);
		LT_value = Lightpercentage;
		  printf("%f\r\n",LT_value); 
		//sensor_Luminance_Upload(LT_value);
		sprintf(LT_Buf,"LightValue: %.2f%%",Lightpercentage);
	}
	else if(LT_ALLValue<100)
	{
		
		printf("LightValue: %d   light alarm!!!\r\n",LT_ALLValue);
		LT_value = LT_ALLValue;
		//sensor_Luminance_Upload(LT_alarm_value);
		sprintf(LT_Buf,"LightValue: %.2f%%",Lightpercentage);
	}
//	Lightpercentage=(Lightpercentage-100);
//	Lightpercentage=-Lightpercentage;
//		//sprintf(Dis_VA_Buf,"  %d   ",ADC_ConvertedValue);
//	printf("LightValue: %.2f%%\r\n",Lightpercentage);
////	printf("LightValue: %d\r\n",ADC_ConvertedValue);
    DMA_ClearFlag(DMA1_FLAG_TC1); 
}





//void ADC_LT_Change_AD(void)
//{
//    if (adcFlag == 0)
//    {
//        delay_ms(500);
//        printf("Start Read LightValue!\r\n");
//        ReadLTValue();
////        delay_ms(500);
////        Get_Light_value();
//       adcFlag = 0;
//    }
//    else if (adcFlag == 1)
//    {
//        delay_ms(500);
//        printf("Start Read DCValue!\r\n");
//        ReadDCValue();
////        delay_ms(500);
////        Get_battery_volt();
//        adcFlag = 0; // 切换回初始状态
//    }
//}



