/*
*********************************************************************************************************
*
*	模块名称 : 串口多路复用以及电子开关控制
*	文件名称 : bsp_Modifyregister.c
*	版    本 : V1.2
*	说    明 : 
*
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2023.4.26  刘斌    usarttest
*
*
*********************************************************************************************************
*/


#include "bsp.h"



char Register_Buf[3] =  {0x00,0x19,0x01};
//char Wegister_Buf1[4] = {Wegister,Addr_Reg,Number,Addr1};
//char Wegister_Buf2[4] = {Wegister,Addr_Reg,Number,Addr2};
char Reset_Lora[3] =    {0x80,0x22,0x01};


/*
*********************************************************************************************************
*	函 数 名: Config_MDPin
*	功能说明: //初始化MD0 MD1引脚 ： 	PB4\PB5
            //初始化串口1的（4路）多路复用控制引脚：USART1_EX_0/USART1_EX_1 : PB3/PA15  
            //初始化串口2的（2路）多路复用控制引脚：LORA_EX_EN : PA4
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/	
void Config_MDPin(void)
{
	// 初始化GPIOB时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE ); //配置复用时钟
		//GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, DISABLE); //全功能SW+JTAG，禁用JTRST，PB4可用
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //启用SW，禁用JTAG，PA15、PB3、PB4可用
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); //完全禁用SW+JTAG，PA13、PA14、PA15、PB3、PB4可用
	
	
		// 配置PB4和PB5引脚为推挽输出模式
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = USART1_EX_0|LORA_MD0| LORA_MD1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // GPIO速度为50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	  // 配置PB4和PB5引脚为推挽输出模式
	  GPIO_InitStructure.GPIO_Pin = LORA_EX_EN| USART1_EX_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // GPIO速度为50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    
	// 将PB4和PB5引脚输出低电平
   
}


/*
*********************************************************************************************************
*	函 数 名: Config_EnSensorPin
*	功能说明: 
            //初始化GPS\CO2&LANYA\ADC电池电压采样电路的电子开关引脚控制，降低Lora节点功耗
             CO2_LANYA_EN :PB0  ADC_DC_EN :PB12  GPS_EN:PA7
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void Config_EnSensorPin(void)
{
	// 初始化GPIOB时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE ); //配置复用时钟
	  //GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE); //全功能SW+JTAG，禁用JTRST，PB4可用
	
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //启用SW，禁用JTAG，PA15、PB3、PB4可用
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); //完全禁用SW+JTAG，PA13、PA14、PA15、PB3、PB4可用
		// 配置PB0和PB12引脚为推挽输出模式
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = CO2_EN|ADC_DC_EN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // GPIO速度为50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// 配置PA7引脚为推挽输出模式
   
    GPIO_InitStructure.GPIO_Pin = GPS_EN|LANYA_EN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // GPIO速度为50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/*
*********************************************************************************************************
*	函 数 名: Reset_MDPin/Set_MDPin/Work_MDPin/Sleeping_MDPin
*	功能说明: 改变Lora模块的配置引脚，若不配置，悬空MD0 MD1 为高电平，模式为低功耗模式
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/	
void Reset_MDPin(void)
{
	 GPIO_ResetBits(GPIOB, GPIO_Pin_4| GPIO_Pin_5);
}




void Set_MDPin(void)
{
	// 将PB4和PB5引脚输出高电平
    GPIO_SetBits(GPIOB, GPIO_Pin_4 | GPIO_Pin_5);
	  delay_ms(20);
}

//开启工作模式
void Work_MDPin(void)
{
	// 将PB4和PB5引脚输出高电平
    GPIO_SetBits(GPIOB, GPIO_Pin_4 );
	  GPIO_ResetBits(GPIOB,  GPIO_Pin_5);
	  delay_ms(20);
}
//开启睡眠模式
void Sleeping_MDPin(void)
{
	// 将PB4和PB5引脚输出高电平
    GPIO_SetBits(GPIOB, GPIO_Pin_4 );
	  GPIO_SetBits(GPIOB,  GPIO_Pin_5);
	  delay_ms(20);
}


void Search_Register(void)
{
		Reset_MDPin();
	  delay_ms(20);
//		lora_send_Byte(0X00);
//		lora_send_Byte(0X18);
//		lora_send_Byte(0X01);
	
	
//	 lora_send_Byte(0X80);
//		lora_send_Byte(0X18);
//		lora_send_Byte(0X01);
//	  lora_send_Byte(0X01);
//	  delay_ms(20);
//	////	delay_ms(20);
//		Set_MDPin();
//		delay_ms(20);
//	Reset_MDPin();
			lora_send_Byte(0X00);
		lora_send_Byte(0X19);
		lora_send_Byte(0X01);
	
}

//信道20功率21空速9.6k
void Modify_Register(void)
{
	Reset_MDPin();
	delay_ms(20);
//	lora_send_Byte(0X00);
//	lora_send_Byte(0X06);
//	lora_send_Byte(0X01);
//	delay_ms(20);
//	
//	lora_send_Byte(0X80);
//	lora_send_Byte(0X06);
//	lora_send_Byte(0X01);
//	lora_send_Byte(0X02);
//	lora_send_Byte(0X9B);
//	delay_ms(20);
//	
//	lora_send_Byte(0X00);
//	lora_send_Byte(0X07);
//	lora_send_Byte(0X01);
//	delay_ms(20);
//	
	lora_send_Byte(0X80);
	lora_send_Byte(0X07);
   lora_send_Byte(0X01);
	lora_send_Byte(0X00);
	lora_send_Byte(0X02);
	delay_ms(20);
//	
	Set_MDPin();
	delay_ms(20);
	Reset_MDPin();
	delay_ms(20);
	
//	lora_send_Byte(0X00);
//	lora_send_Byte(0X07);
//	lora_send_Byte(0X01);
//	delay_ms(20);
//	
//	lora_send_Byte(0X00);
//	lora_send_Byte(0X06);
//	lora_send_Byte(0X01);
//	delay_ms(20);
////	Lora_Send_Buf(Register_Buf,3);//读出目前地址
//	//delay_ms(200);
//	Lora_Send_Buf(Wegister_Buf1,4);//写入新地址
//	delay_ms(20);
//////	Lora_Send_Buf(Reset_Lora,4);//复位模块
//Set_MDPin();
//	delay_ms(20);
//	Reset_MDPin();
//  Lora_Send_Buf(Register_Buf,3);//读出改变后的地址
//	delay_ms(20);
//	Lora_Send_Buf(Wegister_Buf2,4);//写入新地址
//	delay_ms(20);
////	Lora_Send_Buf(Reset_Lora,4);//复位模块
////	delay_ms(20);
//	Set_MDPin();
//	delay_ms(20);
//	Reset_MDPin();
//	Lora_Send_Buf(Register_Buf,3);//读出改变后的地址
}



void Modify_Addr(void)
{
		Reset_MDPin();
	  delay_ms(20);
		lora_send_Byte(0X80);
		lora_send_Byte(0X19);
		lora_send_Byte(0X01);
	  lora_send_Byte(0X22);
	  delay_ms(20);
	////	delay_ms(20);
		Set_MDPin();
		delay_ms(20);
	//Reset_MDPin();
	
}


/*
*********************************************************************************************************
*	函 数 名: CO2_LANYA_SensorEN/ADC_DC_EN_SensorEN/GPS_EN_SensorEN
*	功能说明: 开启GPS\CO2&LANYA\ADC电池电压采样电路的电子开关引脚控制
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/	
//开启CO2检测---------------功耗高
void CO2_SensorEN(void)
{
	 GPIO_SetBits(GPIOB, CO2_EN);
}

//开启经典蓝牙
void LANYA_SensorEN(void)
{
	 GPIO_SetBits(GPIOA, LANYA_EN);
}

//开启ADC电池电压检测---------------功耗高
void ADC_DC_EN_SensorEN(void)
{
	 GPIO_SetBits(GPIOB, ADC_DC_EN);
}

//开启GPS，获取经纬度，海拔高度---------------功耗高
void GPS_EN_SensorEN(void)
{
	 GPIO_SetBits(GPIOA, GPS_EN);
}
//关闭CO2检测---------------功耗高
void CO2_SensorCS(void)
{
	 GPIO_ResetBits(GPIOB, CO2_EN);
}

//关闭经典蓝牙
void LANYA_SensorCS(void)
{
	 GPIO_ResetBits(GPIOA, LANYA_EN);
}

//关闭ADC电池电压检测---------------功耗高
void ADC_DC_EN_SensorCS(void)
{
	 GPIO_ResetBits(GPIOB, ADC_DC_EN);
}

//关闭GPS，获取经纬度，海拔高度---------------功耗高
void GPS_EN_SensorCS(void)
{
	 GPIO_ResetBits(GPIOA, GPS_EN);
}
/*
*********************************************************************************************************
*	函 数 名: USART1_Lanya/USART1_CO2/USART1_Printf/USART1_RESERVED
*	功能说明: 串口1的（4路）多路复用,改变串口1的（4路）多路复用配置引脚，若不配置，悬空MD0 MD1 为低电平，连接蓝牙
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/	
//切换串口为蓝牙
void USART1_Lanya(void)
{
	 GPIO_ResetBits(GPIOB, USART1_EX_0);
	 GPIO_ResetBits(GPIOA, USART1_EX_1);
}

//切换串口CO2
void USART1_CO2(void)
{
	 GPIO_SetBits(GPIOB, USART1_EX_0);
	 GPIO_ResetBits(GPIOA, USART1_EX_1);
}


//切换串口为打印输出
void USART1_Printf(void)
{
	 GPIO_ResetBits(GPIOB, USART1_EX_0);
	 GPIO_SetBits(GPIOA, USART1_EX_1);
}


//切换串口为预留串口
void USART1_RESERVED(void)
{
	 GPIO_SetBits(GPIOB, USART1_EX_0);
	 GPIO_SetBits(GPIOA, USART1_EX_1);
}


/*
*********************************************************************************************************
*	函 数 名: USART2_LORA_EX_EN/USART2_REGLORA_TXD
*	功能说明: 串口2的（2路）多路复用,改变串口2的（2路）多路复用配置引脚，若不配置，悬空LORA_EX_EN 为低电平，
   LORA连接配置串口
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
//切换串口为LORA正常工作
void USART2_REGLORA_TXD(void)
{
	 GPIO_SetBits(GPIOA, LORA_EX_EN);
	 
}

//v切换串口为LORA连接配置串口
void USART2_LORA_EX_EN(void)
{
	 GPIO_ResetBits(GPIOA, LORA_EX_EN);
	 
}

