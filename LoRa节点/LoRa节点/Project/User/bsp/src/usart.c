/**
	************************************************************
	************************************************************
	************************************************************
	*	文件名： 	usart.c
	*
	*
	*	版本： 		V1.0
	*
	*	说明： 		单片机串口外设初始化，格式化打印
	*
	*	修改记录：	
	************************************************************
	************************************************************
	************************************************************
**/

//硬件驱动

#include "bsp.h"

//C库

uint32_t rxd_cnt = 0;//接收计数变量

//usart2 USART2_IRQHandler 数据包
uint8_t txd_buf[4] ={1,2,3,4};
char rxd_buf[100];   //固定包长
uint8_t rxd_flag =0;   //标志位
uint8_t rxd_index = 0;  //索引


/////////////////////////////////////////
char TP_Frist_Buf[4] = {"Temp"};
char TP_End_Buf[4] = {"TD"};//TEMPEND->TD
char GPS_Frist_Buf[4] = {"GPS"};
char GPS_End_Buf[4] = {"GD"};//GPSEND->GD
char Fengge_Bud[10] = {"________"};
/////////////////////////////////////////

#if 1

/*
*********************************************************************************************************
*	函 数 名: fputc
*	功能说明: 重新定义put函数，这样可以使用printf函数从串口1打印输出
*******************************************************************8
	这句话是使用C/C++编程语言中的 `sprintf` 函数来格式化字符串的一部分。
		让我来解释一下它的含义：
1. `sprintf`: 这是一个用于格式化字符串的函数，
		它可以将数据按照指定的格式插入到字符串中。
2. `String`: 这是一个用于存储最终格式化结果的字符数组或字符串变量。
3. `" %.2f%%"`: 这是格式化字符串的格式控制部分。让我们逐个解释它：
	 - `" "`: 这表示在插入数据之前留出一个空格。这是可选的，
		用于在数据前添加一个空格。
	 - `%.2f`: 这是一个格式说明符，用于插入浮点数。
		其中，`%` 表示格式说明符的开始，`.2` 表示保留两位小数，而 `f` 表示浮点数。
	 - `%%`: 这是用来插入百分号的转义序列。因为 `%` 在格式化字符串中是一个特殊字符，
		所以为了插入实际的 `%` 符号，需要使用 `%%`。
4. `Hum`: 这是一个变量，表示要插入到格式化字符串中的具体浮点数值。
综合起来，这句话的意思是将变量 `Hum` 的值按照带有两位小数的浮点数格式，
插入到字符串中，而且会在数值前添加一个空格，并且在数值后添加一个百分号。
例如，如果 `Hum` 的值是 75.25，那么格式化后的结果可能是 `" 75.25%"`。
AHT10ReadData(float *temperature,u8 *humidity);
sprintf(String, "+%.2fC", temperature);//格式化字符串输出到字符串变量

*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
  #pragma import(__use_no_semihosting) /*标准库需要的支持函数*/
  struct __FILE
  {
	  int handle;

  };

   FILE __stdout;
  /*定义_sys_exit()以避免使用半主机模式*/
 void _sys_exit(int x)
  {
	x=x; 

  }
	
 int fputc(int ch,FILE*f)
  {
	while((USART1->SR&0X40)==0){};  //循环发送直到发送完毕
    USART1->DR=(u8)ch;
	return ch;
  }

#endif
  
	
#if EN_USART2_RX //如果使能了接收
//串口2中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	


/*
************************************************************
*	函数名称：	Usart1_Init
*
*	函数功能：	串口1初始化
*
*	入口参数：	baud：设定的波特率
*
*	返回参数：	无
*
*	说明：		TX-PA9		RX-PA10
************************************************************
*/
void Usart1_Init(unsigned int baud)
{

	GPIO_InitTypeDef gpioInitStruct;
	USART_InitTypeDef usartInitStruct;
	NVIC_InitTypeDef nvicInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//PA9	TXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_9;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);
	
	//PA10	RXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_10;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);
	
	usartInitStruct.USART_BaudRate = baud;
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//无硬件流控
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//接收和发送
	usartInitStruct.USART_Parity = USART_Parity_No;									//无校验
	usartInitStruct.USART_StopBits = USART_StopBits_1;								//1位停止位
	usartInitStruct.USART_WordLength = USART_WordLength_8b;							//8位数据位
	USART_Init(USART1, &usartInitStruct);
	
	USART_Cmd(USART1, ENABLE);														//使能串口
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);									//使能接收中断
	
	nvicInitStruct.NVIC_IRQChannel = USART1_IRQn;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	nvicInitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&nvicInitStruct);

}
/*
************************************************************
*	函数名称：	Usart2_Init
*
*	函数功能：	串口2初始化
*
*	入口参数：	baud：设定的波特率
*
*	返回参数：	无
*
*	说明：		TX-PA2		RX-PA3
************************************************************
*/
void Usart2_Init(unsigned int baud)
{

	GPIO_InitTypeDef gpioInitStruct;
	USART_InitTypeDef usartInitStruct;
	NVIC_InitTypeDef nvicInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	//PA2	TXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_2;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);
	
	//PA3	RXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_3;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);
	
	usartInitStruct.USART_BaudRate = baud;
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//无硬件流控
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//接收和发送
	usartInitStruct.USART_Parity = USART_Parity_No;									//无校验
	usartInitStruct.USART_StopBits = USART_StopBits_1;								//1位停止位
	usartInitStruct.USART_WordLength = USART_WordLength_8b;							//8位数据位
	USART_Init(USART2, &usartInitStruct);
	
	USART_Cmd(USART2, ENABLE);														//使能串口
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);									//使能接收中断
	
	nvicInitStruct.NVIC_IRQChannel = USART2_IRQn;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 3;
	nvicInitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&nvicInitStruct);

}



/*
************************************************************
*	函数名称：	Usart3_Init
*
*	函数功能：	串口3初始化
*
*	入口参数：	baud：设定的波特率
*
*	返回参数：	无
*
*	说明：		TX-PB10		RX-PB11
************************************************************
*/
void Usart3_Init(unsigned int baud)
{

	GPIO_InitTypeDef gpioInitStruct;
	USART_InitTypeDef usartInitStruct;
	NVIC_InitTypeDef nvicInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	//PA2	TXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_10;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpioInitStruct);
	
	//PA3	RXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_11;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpioInitStruct);
	
	usartInitStruct.USART_BaudRate = baud;
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//无硬件流控
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//接收和发送
	usartInitStruct.USART_Parity = USART_Parity_No;									//无校验
	usartInitStruct.USART_StopBits = USART_StopBits_1;								//1位停止位
	usartInitStruct.USART_WordLength = USART_WordLength_8b;							//8位数据位
	USART_Init(USART3, &usartInitStruct);
	
	USART_Cmd(USART3, ENABLE);														//使能串口
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);									//使能接收中断
	
	nvicInitStruct.NVIC_IRQChannel = USART3_IRQn;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 3;
	nvicInitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&nvicInitStruct);

}


/*
************************************************************
*	函数名称：	Usart_SendByte
*
*	函数功能：	串口数据发送
*
*	入口参数：	USARTx：串口组
*				发送字节
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/

void lora_send_Byte(char Byte)
{
	USART_SendData(USART2,Byte);
	/*等待发送完成DR寄存器为空*/
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);		//等待发送完成
}

void lora_send_buf(char *buf, uint16_t len)
{
	uint16_t i;
	for(i= 0;i<len;i++)
	{
		lora_send_Byte(buf[i]);
	}
}

//直接发送数组即可打印
void lora_send_string(uint8_t *str)
{
	while(*str != '\0')
	{
		lora_send_Byte(*str++);
	}
}



void lanya_send_Byte(char Byte)
{
	USART_SendData(USART1,Byte);
	/*等待发送完成DR寄存器为空*/
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		//等待发送完成
}


//直接发送数组即可打印
void send_string(uint8_t *str)
{
	while(*str != '\0')
	{
		lanya_send_Byte(*str++);
	}
}
/*
************************************************************
*	函数名称：	Usart_SendString
*
*	函数功能：	串口数据发送
*
*	入口参数：	USARTx：串口组
*				str：要发送的数据
*				len：数据长度
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len)
{

	unsigned short count = 0;
	
	for(; count < len; count++)
	{
		USART_SendData(USARTx, *str++);									//发送数据
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);		//等待发送完成
	}

}


/************************************************************************************************
 * 函 数 名: USART1_SendData
 * 函数功能: 发送len个字节数据
 * 函数参数: buf(缓冲区首地址),len(字节长度0-255)
 * 返 回 值: 无
 ***********************************************************************************************/
void USART1_SendData(uint8_t *buf, uint8_t len)
{
    uint8_t t;
    
    for(t = 0; t < len; t++)
    {
        while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
        USART_SendData(USART1, buf[t]);
    }
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}



/************************************************************************************************
 * 函 数 名: USART2_SendData
 * 函数功能: 发送len个字节数据
 * 函数参数: buf(缓冲区首地址),len(字节长度0-255)
 * 返 回 值: 无
 ***********************************************************************************************/
void USART2_SendData(uint8_t *buf, uint8_t len)
{
    uint8_t t;
    
    for(t = 0; t < len; t++)
    {
        while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
        USART_SendData(USART2, buf[t]);
    }
    while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
}




/*
************************************************************
*	函数名称：	Usart_SendBuf
*
*	函数功能：	串口数据发送
*
*	入口参数：	USARTx：串口组
*				发送一串数据
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/

void lanya_send_buf(char *buf, uint16_t len)
{
	uint16_t i;
	for(i= 0;i<len;i++)
	{
		lanya_send_Byte(buf[i]);
	}
}


void Lanya_Send_Pack(void)
{

		lanya_send_Byte('A');
	  lanya_send_buf(rxd_buf,rxd_index);
	  lanya_send_Byte('\r');
	  lanya_send_Byte('\n');
	  rxd_index=0;
	
}


/*
************************************************************
*	函数名称：	UsartPrintf
*
*	函数功能：	格式化打印
*
*	入口参数：	USARTx：串口组
*				fmt：不定长参
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...)
{

	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;
	
	va_start(ap, fmt);
	vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap);							//格式化
	va_end(ap);
	
	while(*pStr != 0)
	{
		USART_SendData(USARTx, *pStr++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}

}




/*
************************************************************
*	函数名称：	USART1_IRQHandler
*
*	函数功能：	格式化打印
*
*	入口参数：	USARTx：串口组
*				fmt：不定长参
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void USART1_IRQHandler(void)
{
    uint8_t Res;
    static uint8_t Res_state = 0;
   lanya_send_Byte(Res);

    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        Res = USART_ReceiveData(USART1);

        switch (Res_state)
        {
        case 0: // 帧头1
            if (Res == 0x42 && rxd_flag == 0)
            {
                rxd_index = 0;
                rxd_buf[rxd_index++] = Res;
                Res_state = 1;
            }else if(Res == 'A')
										{
											Res_state = 4;
										}
            else
            {
                Res_state = 0;
            }
						LED0 = 0;
            break;

        case 1: // 帧头2
            if (Res == 0x4D)
            {
                rxd_buf[rxd_index++] = Res;
                Res_state = 2;
            }
            else
            {
                Res_state = 0;
            }
            break;

        case 2: // 数据
            rxd_buf[rxd_index++] = Res;

            if (rxd_index >= 16) // 固定包长15个
            {
                Res_state = 3;
            }
						LED0 = 1;
            break;

        case 3: // 校验和
           
				    rxd_flag = 1;
            // 清空状态，准备下次接收
            Res_state = 0;
           

            break;
				
        case 4: 
					
					 if(Res == 'B')
							{
								printf("Hello!Can I help you? \r\n 1.Reply AC:We will printf this Node. \r\n 2.Reply AD:We will Send a distress signal!\r\n");
							}
							else if(Res == 'C')
							{
								printf("We will..CCC");
							}
							else if(Res == 'D')
							{
								printf("We will..DDD");
							}
           break;
			 
        }

        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}


	

/*
************************************************************
*	函数名称：	USART2_IRQHandler
*
*	函数功能：	格式化打印
*
*	入口参数：	USARTx：串口组
*				fmt：不定长参
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void USART2_IRQHandler(void)                   //串口1中断服务程序
{
		
		
	
	uint8_t Res;
	static uint8_t  Res_state = 0;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)  //接收中断（接收到一个字节数据）
	{
		Res = USART_ReceiveData(USART2);     //把接收到的字节保存
	  switch(Res_state)
		{
			case 0:    //'A' 为文本模式发送/或者ASCII码
				if((Res=='A')&& !rxd_flag)  //判断帧头 && 防止丢包
				{
					Res_state=1;  //切换为下一个状态
					rxd_index=0;  //将索引归0，方便下次接着接收
				}
				else{
					Res_state=0;  //帧头不对，死循环
				}
			  LED0 = 1;   
			break;
			case 1:
				if(Res=='\r')
				{
					Res_state=2;   //进入下一个状态
				}
				else
				{
					rxd_buf[rxd_index] = Res;  //将接下来的数据存入BUF
		  	  rxd_index++;    //一个个存
				}
				LED0 = 0;  
			 break; 
			case 2:
				if(Res=='\n')
				{
					rxd_flag=1;      //切换标志位，代表数据接收完成
					Res_state=0;     //清除状态，方便下次接收
				} 
				break;
		}
		
	}
     USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	   //USART_ClearITPendingBit(USART1,USART_IT_IDLE);
  }


void Lora_SendAllInformation(void)
{
	
	//温湿度
	//lora_send_buf(TP_Frist_Buf,4);
//	 lora_send_buf(buffer_temp,30);
//	delay_ms(20);
//		lora_send_buf(buffer_hum,30);
//	delay_ms(20);
	lora_send_buf(TP_End_Buf,4);
	
	//GPS信息
	lora_send_buf(GPS_Frist_Buf,4);
	lora_send_buf(Time_BUF,30);
	delay_ms(200);
	lora_send_buf(GPS_BUF,200);
	delay_ms(400);
	lora_send_buf(GPS_End_Buf,4);
	
	//光照电压
	lora_send_buf(DC_Buf,20);
	delay_ms(200);
	lora_send_buf(LT_Buf,20);
	delay_ms(200);
	
	
}


//void Timer_SendBuf(void)
//{
//	    // if(rxd_cnt %11==0)
//			//	{
//					printf("start DC!\r\n");
//					//printf("dc:%d \r\n",adcValueVoltage);	
//					
//	    	  Get_battery_volt();
//					delay_ms(50);
//					lora_send_buf(DC_Buf,20);
//			    
//					lora_send_buf(Fengge_Bud,10);
//			//	}
//				//delay_ms(1000);
//				// if(rxd_cnt %6==0)
//				//	{
//						printf("start AHT10!\r\n");
//		        read_AHT10_once();	
//							
//						lora_send_buf(buffer_temp,30);
//	           delay_ms(20);
//		        lora_send_buf(buffer_hum,30);
//						 delay_ms(20);
//						lora_send_buf(TP_End_Buf,4);
//						
//						lora_send_buf(Fengge_Bud,10);
//						printf("TEMP FINISH!\r\n");
//						printf("start Light!\r\n");
//	          Get_Light_value();	
//						 delay_ms(20);
//						lora_send_buf(LT_Buf,20);
//	           delay_ms(20);
//						
//						lora_send_buf(Fengge_Bud,10);
//			    
//					//delay_ms(1000);
//					// if(rxd_cnt %16==0)
//					
//							printf("start GPS!\r\n");
//							printGpsBuffer();
//							delay_ms(20);
//						  lora_send_buf(GPS_Frist_Buf,4);
//	            lora_send_buf(Time_BUF,30);
//						
//						lora_send_buf(Fengge_Bud,10);
//						  delay_ms(20);
//							lora_send_buf(GPS_BUF,100);
//							delay_ms(500);
//							lora_send_buf(GPS_End_Buf,4);
//						
//						lora_send_buf(Fengge_Bud,10);
//							printf("GPS FINISH!\r\n");
//							//Lora_SendAllInformation();
//							//delay_ms(500);
//						  clrStruct();
//						//  delay_ms(50);
//						
//				//	}
//					delay_ms(1000);
//}




#endif


