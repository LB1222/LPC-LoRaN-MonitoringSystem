/*
*********************************************************************************************************
*
*	模块名称 : CO2驱动模块
*	文件名称 : bsp_CO2.c
*	版    本 : V1.0
*	说    明 : 获得二氧化碳传感器的数据并计算出值。数据使用串口1接收，传感器受电子开关控制。
            传感器接收数据受多路复用器控制，具体查看bsp_Modifyregister.c文件有具体说明
*
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2024-02-19  刘斌  正式发布
*
*	
*
*********************************************************************************************************
*/

#include "bsp.h"

char Co2ValueString[20];
float CO2_value ;
/*
************************************************************
*	函数名称：	ComparisonChecksum
*
*	函数功能：	对比校验和是否正确
							数据头： BYTE0 = 0X42；BYTE1=4D 
							BYTE6 数据高位，BYTE7数据低位，表示CO2浓度。
							 BYTE15,数据校验和. BYTE15= BYTE0+BYTE1+…….+BYTE14; 
							 例: 42 4D 0C 51 09 A2 07 2B 01 35 05 81 20 08 00 AD; 
							CO2浓度= BYTE6 X 256 + BYTE7 =07X256 + 2B = 1835;
*
*	入口参数：	USARTx：串口组
*				
*
*	返回参数：	无
*
*	说明：	char sum = 0;		uint8_t sum = 0;  sum得出的结果都一样？
          sum = sum & 0xFF;  保留 sum 的最低8位，而将高位清零。 但是有没有结果都正确？
************************************************************
*/
//对比校验和是否正确，将flag == 0;

void ComparisonChecksum (void)
{
	char sum = 0;
	uint8_t i=0;
	if(rxd_flag == 1)
	{
		for(i=0;i<15;i++)
		{
			sum +=rxd_buf[i];
		}
			sum = sum & 0xFF;
	
			 if( rxd_buf [15] == sum)
			{				
				// lora_send_buf(rxd_buf,16);
	       rxd_flag=0;			
			}
	}
	// 计算校验和，只考虑前15个字节
    
	 
}

/*
************************************************************
*	函数名称：	Calculate_Co2Value
*
*	函数功能：	计算CO2的值
							
							BYTE6 数据高位，BYTE7数据低位，表示CO2浓度。
							  
							 例: 42 4D 0C 51 09 A2 07 2B 01 35 05 81 20 08 00 AD; 
							CO2浓度= BYTE6 X 256 + BYTE7 =07X256 + 2B = 1835;
*
*	入口参数：	USARTx：串口组
*				
*
*	返回参数：	无
*
*	说明：	传感器为C8D是一款采用NDIR 气体传感器技术测量室内空气中二氧化碳浓度的迷
   你型双通红外二氧化碳传感器模块。价格较贵精度较高±(50ppm+5%读数),
   可替换为：JW01-CO2-V2.2 数字信号，很便宜
************************************************************
*/

void Calculate_Co2Value(void)
{
  	 uint8_t i;
		 long int  Co2Value=0;
	//	 char Co2ValueString[20];
	// 起始位置和要转换的字节数
		 uint8_t start = 6;
		 uint8_t length = 2;
	// 使用 strtol 函数将十六进制数转换为十进制数
     char *endptr;

    // 构建要转换的子串
    char hexNumber[length * 2 + 1]; // 每个字节占两个十六进制字符，再加上字符串结束符
    for (i = 0; i < length; ++i) {
        sprintf(hexNumber + 2 * i, "%02X", rxd_buf[start + i]);
    }
    hexNumber[length * 2] = '\0'; // 添加字符串结束符
		
     Co2Value = strtol(hexNumber, &endptr, 16);
		 if (*endptr != '\0') {
        // 处理错误，比如记录错误消息或采取适当的措施
        lora_send_Byte(0xFF);
    }
		 
		 // 输出结果
    printf("Hexadecimal: %s\n", hexNumber);
    printf("Co2Value: %ld\n", Co2Value);
		//lora_send_Byte(Co2Value);
		 sprintf(Co2ValueString, " %ld", Co2Value);
		
		CO2_value = atof(Co2ValueString);
		printf("%f\r\n",CO2_value);
		 //lora_send_buf(Co2ValueString,14);
//     Usart_SendString(USART2,Co2ValueString,5);
}



/*
*********************************************************************************************************
*	函 数 名: LowPower_Calculate_Co2Value
*	功能说明: 低功耗模式下计算获取CO2的值，实测至少连续读取30s
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void LowPower_Calculate_Co2Value(void)
{
	    
			for(int i=0;i<5;i++)
						{
							for(int j = 0;j<10;j++)
							{
								USART1_CO2();
							  delay_ms(20);
							  ComparisonChecksum();
							}
							 
								//USART1_Printf();
							 USART1_Lanya();
								delay_ms(30);
								Calculate_Co2Value();	
								delay_ms(20);
						}
}
