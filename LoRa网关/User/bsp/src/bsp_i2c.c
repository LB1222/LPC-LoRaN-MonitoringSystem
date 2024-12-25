
/*
*********************************************************************************************************
*
*	模块名称 : AHT10驱动模块
*	文件名称 : bsp_I2C.c
*	版    本 : V1.0
*	说    明 : 驱动aht10温湿度模块，配合新建工程使用，非完整文件
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


char buffer_temp[30]; // 用于存储格式化后的temp字符串
char buffer_hum[30]; // 用于存储格式化后的hum字符串
float Local_Temp_value;
float Local_Hum_value;


uint32_t CT_data[2];
volatile int  c1,t1;
u8 ret=0;

void Delay_N10us(uint32_t t)//延时函数
{
  uint32_t k;

   while(t--)
  {
    for (k = 0; k < 2; k++)//110
      ;
  }
}



void SensorDelay_us(uint32_t t)//延时函数
{
	t = t-2;	
	for(; t>0; t--)
	{
		Delay_N10us(1);
	}

}

void Delay_3us(void)		//延时函数
{	
	Delay_N10us(1);
	Delay_N10us(1);
	Delay_N10us(1);
	Delay_N10us(1);
}
void Delay_1us(void)		//延时函数
{	
	Delay_N10us(1);
	Delay_N10us(1);
	Delay_N10us(1);
	Delay_N10us(1);
	Delay_N10us(1);

}


void SDA_Pin_Output_High(void)   // 将 P15 配置为输出， 并设置为高电平， P15 作为 I2C 的 SDA
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_SetBits(GPIOB, GPIO_Pin_6);
}

void SDA_Pin_Output_Low(void)  // 将 P15 配置为输出  并设置为低电平
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_ResetBits(GPIOB, GPIO_Pin_6);
}

void SDA_Pin_IN_FLOATING(void)  // SDA 配置为悬浮输入
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void SCL_Pin_Output_High(void) // SCL 输出高电平，P14 作为 I2C 的 SCL
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_SetBits(GPIOB, GPIO_Pin_7);
}

void SCL_Pin_Output_Low(void) // SCL 输出低电平
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_ResetBits(GPIOB, GPIO_Pin_7);
}

void Init_I2C_Sensor_Port(void) // 初始化 I2C 接口
{
    SDA_Pin_Output_High(); // 将 P15 配置为开漏输出  并设置为高电平
    SCL_Pin_Output_High(); // 将 P14 配置为开漏输出  并设置为高电平
}


void I2C_Start(void)		 //I2C主机发送START信号
{
 SDA_Pin_Output_High();
 SensorDelay_us(8);
 SCL_Pin_Output_High();
 SensorDelay_us(8);
 SDA_Pin_Output_Low();
 SensorDelay_us(8);
 SCL_Pin_Output_Low();
 SensorDelay_us(8);   
}


void ZSSC_I2C_WR_Byte(uint8_t Byte) //往AHT10写一个字节
{
	uint8_t Data,N,i;	
	Data=Byte;
	i = 0x80;
	for(N=0;N<8;N++)
	{
		SCL_Pin_Output_Low();
	  
		Delay_3us();	
		
		if(i&Data)
		{
			SDA_Pin_Output_High();
		}
		else
		{
			SDA_Pin_Output_Low();
		}	
			
        SCL_Pin_Output_High();
		Delay_3us();
		
		Data <<= 1;
		 
	}
	SCL_Pin_Output_Low();
	SensorDelay_us(8);   
	SDA_Pin_IN_FLOATING();
	SensorDelay_us(8);	
}	


uint8_t ZSSC_I2C_RD_Byte(void)//从AHT10读取一个字节
{
	uint8_t Byte,i,a;
	Byte = 0;
	SCL_Pin_Output_Low();
	SDA_Pin_IN_FLOATING();
	SensorDelay_us(8);	
	for(i=0;i<8;i++)
	{
    SCL_Pin_Output_High();		
		Delay_1us();
		a=0;
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)) a = 1;

		Byte = (Byte<<1)|a;
		SCL_Pin_Output_Low();
		Delay_1us();
	}
    SDA_Pin_IN_FLOATING();
	SensorDelay_us(8);	
	return Byte;
}


uint8_t Receive_ACK(void)   //看AHT10是否有回复ACK
{
	uint16_t CNT;
	CNT = 0;
	SCL_Pin_Output_Low();	
	SDA_Pin_IN_FLOATING();
	SensorDelay_us(8);	
	SCL_Pin_Output_High();	
	SensorDelay_us(8);	
	while((GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6))  && CNT < 100) 
	CNT++;
	if(CNT == 100)
	{
		return 0;
	}
 	SCL_Pin_Output_Low();	
	SensorDelay_us(8);	
	return 1;
}

void Send_ACK(void)		  //主机回复ACK信号
{
	SCL_Pin_Output_Low();	
	SensorDelay_us(8);	
	SDA_Pin_Output_Low();
	SensorDelay_us(8);	
	SCL_Pin_Output_High();	
	SensorDelay_us(8);
	SCL_Pin_Output_Low();	
	SensorDelay_us(8);
	SDA_Pin_IN_FLOATING();
	SensorDelay_us(8);
}

void Send_NOT_ACK(void)	//主机不回复ACK
{
	SCL_Pin_Output_Low();	
	SensorDelay_us(8);
	SDA_Pin_Output_High();
	SensorDelay_us(8);
	SCL_Pin_Output_High();	
	SensorDelay_us(8);		
	SCL_Pin_Output_Low();	
	SensorDelay_us(8);
    SDA_Pin_Output_Low();
	SensorDelay_us(8);
}

void Stop_I2C(void)	  //一条协议结束
{
	SDA_Pin_Output_Low();
	SensorDelay_us(8);
	SCL_Pin_Output_High();	
	SensorDelay_us(8);
	SDA_Pin_Output_High();
	SensorDelay_us(8);
}

uint8_t JH_Read_Status(void)//读取AHT10的状态寄存器
{

	uint8_t Byte_first;	
	I2C_Start();
	ZSSC_I2C_WR_Byte(0x71);
	Receive_ACK();
	Byte_first = ZSSC_I2C_RD_Byte();
		

	Send_NOT_ACK();
	Stop_I2C();


	return Byte_first;
}

uint8_t JH_Read_Cal_Enable(void)  //查询cal enable位有没有使能？
{
	uint8_t val = 0;//ret = 0,
 
  val = JH_Read_Status();
  if((val & 0x68)==0x08)  //判断NOR模式和校准输出是否有效
  return 1;
  else  return 0;
 }



void JH_SendAC(void) //向AHT10发送AC命令
{

 I2C_Start();
 ZSSC_I2C_WR_Byte(0x70);
 Receive_ACK();
 ZSSC_I2C_WR_Byte(0xac);
 Receive_ACK();
 ZSSC_I2C_WR_Byte(0x33);
 Receive_ACK();
 ZSSC_I2C_WR_Byte(0x00);
 Receive_ACK();
 Stop_I2C();

}

void JH_Send_BA(void)//向AHT10发送BA命令
{


 I2C_Start();
 ZSSC_I2C_WR_Byte(0x70);
 Receive_ACK();
 ZSSC_I2C_WR_Byte(0xba);
 Receive_ACK();
 Stop_I2C();


}

void JH_Read_CTdata(uint32_t *ct) //读取AHT10的温度和湿度数据
{
	volatile uint8_t  Byte_1th=0;
	volatile uint8_t  Byte_2th=0;
	volatile uint8_t  Byte_3th=0;
	volatile uint8_t  Byte_4th=0;
	volatile uint8_t  Byte_5th=0;
	volatile uint8_t  Byte_6th=0;
	 uint32_t RetuData = 0;
	
	uint16_t cnt = 0;


	JH_SendAC();//向AHT10发送AC命令

	delay_ms(75);//等待75ms
    cnt = 0;
	while(((JH_Read_Status()&0x80)==0x80))//等待忙状态结束
	{
	 SensorDelay_us(1508);
	 if(cnt++>=100)
	 {
	  break;
	  }
	}
	I2C_Start();

	ZSSC_I2C_WR_Byte(0x71);//0x70+1   0x70为设备地址 1为方向位
	Receive_ACK();
	Byte_1th = ZSSC_I2C_RD_Byte();//状态字
	Send_ACK();
	Byte_2th = ZSSC_I2C_RD_Byte();//湿度字节
	Send_ACK();
	Byte_3th = ZSSC_I2C_RD_Byte();//湿度字节
	Send_ACK();
	Byte_4th = ZSSC_I2C_RD_Byte();//高4位为湿度  低4位为温度
	Send_ACK();
	Byte_5th = ZSSC_I2C_RD_Byte();//温度字节
	Send_ACK();
	Byte_6th = ZSSC_I2C_RD_Byte();//温度字节
	Send_NOT_ACK();
	Stop_I2C();

	RetuData = (RetuData|Byte_2th)<<8;
	RetuData = (RetuData|Byte_3th)<<8;
	RetuData = (RetuData|Byte_4th);
	RetuData =RetuData >>4;
	ct[0] = RetuData;
	RetuData = 0;
	RetuData = (RetuData|Byte_4th)<<8;
	RetuData = (RetuData|Byte_5th)<<8;
	RetuData = (RetuData|Byte_6th);
	RetuData = RetuData&0xfffff;
	ct[1] =RetuData; 

}


u8 JH_Init(void)   //初始化AHT10
{

	int count=0;
	Init_I2C_Sensor_Port();
	SensorDelay_us(11038);

	I2C_Start();
	ZSSC_I2C_WR_Byte(0x70);
	Receive_ACK();
	ZSSC_I2C_WR_Byte(0xe1);//写系统配置寄存器
	Receive_ACK();
	ZSSC_I2C_WR_Byte(0x08);
	Receive_ACK();
	ZSSC_I2C_WR_Byte(0x00);
	Receive_ACK();
	Stop_I2C();

	delay_ms(500);//延时0.5S
   while(JH_Read_Cal_Enable()==0)//需要等待状态字status的Bit[3]=1时才去读数据。如果Bit[3]不等于1 ，发软件复位0xBA给AHT10，再重新初始化AHT10，直至Bit[3]=1
   {
    
	JH_Send_BA();  //复位
	delay_ms(100);
	SensorDelay_us(11038);

	I2C_Start();
	ZSSC_I2C_WR_Byte(0x70);
	Receive_ACK();
	ZSSC_I2C_WR_Byte(0xe1);//写系统配置寄存器
	Receive_ACK();
	ZSSC_I2C_WR_Byte(0x08);
	Receive_ACK();
	ZSSC_I2C_WR_Byte(0x00);
	Receive_ACK();
	Stop_I2C();
	count++;
	if(count>=10)return 0;
	delay_ms(500);
    }
   return 1;
}

void Read_AHT10(void)
{
	ret = JH_Init(); //初始化
		if(ret == 0)
		{ 
		 printf("fail\r\n");
	  }
	
	 while(JH_Read_Cal_Enable()==0)//等到校准输出使能位为1，才读取。
		 {
				JH_Init();//如果为0再使能一次
				delay_ms(30);
		 }
		 JH_Read_CTdata(CT_data);  //读取温度和湿度 ， 可间隔1.5S读一次
		 c1 = CT_data[0]*1000/1024/1024;  //计算得到湿度值（放大了10倍,如果c1=523，表示现在湿度为52.3%）
		 t1 = CT_data[1] *200*10/1024/1024-500;//计算得到温度值（放大了10倍，如果t1=245，表示现在温度为24.5℃）
		 
		 printf("c1:%d\r\n",c1); 
		 printf("t1:%d\r\n",t1); 
		 
		 printf("Temp:%d%d.%d \r\n",t1/100,(t1/10)%10,t1%10);
		 printf("Hum:%d%d.%d \r\n",c1/100,(c1/10)%10,c1%10);
		 sprintf(buffer_temp, "%d%d.%d",t1/100,(t1/10)%10,t1%10);
		 sprintf(buffer_hum, "%d%d.%d",c1/100,(c1/10)%10,c1%10);
		 
	   Local_Temp_value = atof(buffer_temp);
     Local_Hum_value = atof(buffer_hum);
		 
			printf("%f\r\n",Local_Temp_value);
			printf("%f\r\n",Local_Hum_value);
		 
			OLED_Write_Number(3,48,t1/100);
			OLED_Write_Number(3,56,(t1/10)%10);
			OLED_Write_Number(3,72,t1%10);
			OLED_Write_Number(5,48,c1/100);
			OLED_Write_Number(5,56,(c1/10)%10);
			OLED_Write_Number(5,72,c1%10);
}

