/**
	************************************************************
	************************************************************
	************************************************************
	*	�ļ����� 	usart.c
	*
	*
	*	�汾�� 		V1.0
	*
	*	˵���� 		��Ƭ�����������ʼ������ʽ����ӡ
	*
	*	�޸ļ�¼��	
	************************************************************
	************************************************************
	************************************************************
**/

//Ӳ������

#include "bsp.h"

//C��

uint32_t rxd_cnt = 0;//���ռ�������

//usart2 USART2_IRQHandler ���ݰ�
uint8_t txd_buf[4] ={1,2,3,4};
char rxd_buf[100];   //�̶�����
uint8_t rxd_flag =0;   //��־λ
uint8_t rxd_index = 0;  //����


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
*	�� �� ��: fputc
*	����˵��: ���¶���put��������������ʹ��printf�����Ӵ���1��ӡ���
*******************************************************************8
	��仰��ʹ��C/C++��������е� `sprintf` ��������ʽ���ַ�����һ���֡�
		����������һ�����ĺ��壺
1. `sprintf`: ����һ�����ڸ�ʽ���ַ����ĺ�����
		�����Խ����ݰ���ָ���ĸ�ʽ���뵽�ַ����С�
2. `String`: ����һ�����ڴ洢���ո�ʽ��������ַ�������ַ���������
3. `" %.2f%%"`: ���Ǹ�ʽ���ַ����ĸ�ʽ���Ʋ��֡������������������
	 - `" "`: ���ʾ�ڲ�������֮ǰ����һ���ո����ǿ�ѡ�ģ�
		����������ǰ���һ���ո�
	 - `%.2f`: ����һ����ʽ˵���������ڲ��븡������
		���У�`%` ��ʾ��ʽ˵�����Ŀ�ʼ��`.2` ��ʾ������λС������ `f` ��ʾ��������
	 - `%%`: ������������ٷֺŵ�ת�����С���Ϊ `%` �ڸ�ʽ���ַ�������һ�������ַ���
		����Ϊ�˲���ʵ�ʵ� `%` ���ţ���Ҫʹ�� `%%`��
4. `Hum`: ����һ����������ʾҪ���뵽��ʽ���ַ����еľ��帡����ֵ��
�ۺ���������仰����˼�ǽ����� `Hum` ��ֵ���մ�����λС���ĸ�������ʽ��
���뵽�ַ����У����һ�����ֵǰ���һ���ո񣬲�������ֵ�����һ���ٷֺš�
���磬��� `Hum` ��ֵ�� 75.25����ô��ʽ����Ľ�������� `" 75.25%"`��
AHT10ReadData(float *temperature,u8 *humidity);
sprintf(String, "+%.2fC", temperature);//��ʽ���ַ���������ַ�������

*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
  #pragma import(__use_no_semihosting) /*��׼����Ҫ��֧�ֺ���*/
  struct __FILE
  {
	  int handle;

  };

   FILE __stdout;
  /*����_sys_exit()�Ա���ʹ�ð�����ģʽ*/
 void _sys_exit(int x)
  {
	x=x; 

  }
	
 int fputc(int ch,FILE*f)
  {
	while((USART1->SR&0X40)==0){};  //ѭ������ֱ���������
    USART1->DR=(u8)ch;
	return ch;
  }

#endif
  
	
#if EN_USART2_RX //���ʹ���˽���
//����2�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	


/*
************************************************************
*	�������ƣ�	Usart1_Init
*
*	�������ܣ�	����1��ʼ��
*
*	��ڲ�����	baud���趨�Ĳ�����
*
*	���ز�����	��
*
*	˵����		TX-PA9		RX-PA10
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
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//���պͷ���
	usartInitStruct.USART_Parity = USART_Parity_No;									//��У��
	usartInitStruct.USART_StopBits = USART_StopBits_1;								//1λֹͣλ
	usartInitStruct.USART_WordLength = USART_WordLength_8b;							//8λ����λ
	USART_Init(USART1, &usartInitStruct);
	
	USART_Cmd(USART1, ENABLE);														//ʹ�ܴ���
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);									//ʹ�ܽ����ж�
	
	nvicInitStruct.NVIC_IRQChannel = USART1_IRQn;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	nvicInitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&nvicInitStruct);

}
/*
************************************************************
*	�������ƣ�	Usart2_Init
*
*	�������ܣ�	����2��ʼ��
*
*	��ڲ�����	baud���趨�Ĳ�����
*
*	���ز�����	��
*
*	˵����		TX-PA2		RX-PA3
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
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//���պͷ���
	usartInitStruct.USART_Parity = USART_Parity_No;									//��У��
	usartInitStruct.USART_StopBits = USART_StopBits_1;								//1λֹͣλ
	usartInitStruct.USART_WordLength = USART_WordLength_8b;							//8λ����λ
	USART_Init(USART2, &usartInitStruct);
	
	USART_Cmd(USART2, ENABLE);														//ʹ�ܴ���
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);									//ʹ�ܽ����ж�
	
	nvicInitStruct.NVIC_IRQChannel = USART2_IRQn;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 3;
	nvicInitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&nvicInitStruct);

}



/*
************************************************************
*	�������ƣ�	Usart3_Init
*
*	�������ܣ�	����3��ʼ��
*
*	��ڲ�����	baud���趨�Ĳ�����
*
*	���ز�����	��
*
*	˵����		TX-PB10		RX-PB11
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
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//���պͷ���
	usartInitStruct.USART_Parity = USART_Parity_No;									//��У��
	usartInitStruct.USART_StopBits = USART_StopBits_1;								//1λֹͣλ
	usartInitStruct.USART_WordLength = USART_WordLength_8b;							//8λ����λ
	USART_Init(USART3, &usartInitStruct);
	
	USART_Cmd(USART3, ENABLE);														//ʹ�ܴ���
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);									//ʹ�ܽ����ж�
	
	nvicInitStruct.NVIC_IRQChannel = USART3_IRQn;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 3;
	nvicInitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&nvicInitStruct);

}


/*
************************************************************
*	�������ƣ�	Usart_SendByte
*
*	�������ܣ�	�������ݷ���
*
*	��ڲ�����	USARTx��������
*				�����ֽ�
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/

void lora_send_Byte(char Byte)
{
	USART_SendData(USART2,Byte);
	/*�ȴ��������DR�Ĵ���Ϊ��*/
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);		//�ȴ��������
}

void lora_send_buf(char *buf, uint16_t len)
{
	uint16_t i;
	for(i= 0;i<len;i++)
	{
		lora_send_Byte(buf[i]);
	}
}

//ֱ�ӷ������鼴�ɴ�ӡ
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
	/*�ȴ��������DR�Ĵ���Ϊ��*/
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		//�ȴ��������
}


//ֱ�ӷ������鼴�ɴ�ӡ
void send_string(uint8_t *str)
{
	while(*str != '\0')
	{
		lanya_send_Byte(*str++);
	}
}
/*
************************************************************
*	�������ƣ�	Usart_SendString
*
*	�������ܣ�	�������ݷ���
*
*	��ڲ�����	USARTx��������
*				str��Ҫ���͵�����
*				len�����ݳ���
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len)
{

	unsigned short count = 0;
	
	for(; count < len; count++)
	{
		USART_SendData(USARTx, *str++);									//��������
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);		//�ȴ��������
	}

}


/************************************************************************************************
 * �� �� ��: USART1_SendData
 * ��������: ����len���ֽ�����
 * ��������: buf(�������׵�ַ),len(�ֽڳ���0-255)
 * �� �� ֵ: ��
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
 * �� �� ��: USART2_SendData
 * ��������: ����len���ֽ�����
 * ��������: buf(�������׵�ַ),len(�ֽڳ���0-255)
 * �� �� ֵ: ��
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
*	�������ƣ�	Usart_SendBuf
*
*	�������ܣ�	�������ݷ���
*
*	��ڲ�����	USARTx��������
*				����һ������
*
*	���ز�����	��
*
*	˵����		
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
*	�������ƣ�	UsartPrintf
*
*	�������ܣ�	��ʽ����ӡ
*
*	��ڲ�����	USARTx��������
*				fmt����������
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...)
{

	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;
	
	va_start(ap, fmt);
	vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap);							//��ʽ��
	va_end(ap);
	
	while(*pStr != 0)
	{
		USART_SendData(USARTx, *pStr++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}

}




/*
************************************************************
*	�������ƣ�	USART1_IRQHandler
*
*	�������ܣ�	��ʽ����ӡ
*
*	��ڲ�����	USARTx��������
*				fmt����������
*
*	���ز�����	��
*
*	˵����		
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
        case 0: // ֡ͷ1
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

        case 1: // ֡ͷ2
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

        case 2: // ����
            rxd_buf[rxd_index++] = Res;

            if (rxd_index >= 16) // �̶�����15��
            {
                Res_state = 3;
            }
						LED0 = 1;
            break;

        case 3: // У���
           
				    rxd_flag = 1;
            // ���״̬��׼���´ν���
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
*	�������ƣ�	USART2_IRQHandler
*
*	�������ܣ�	��ʽ����ӡ
*
*	��ڲ�����	USARTx��������
*				fmt����������
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void USART2_IRQHandler(void)                   //����1�жϷ������
{
		
		
	
	uint8_t Res;
	static uint8_t  Res_state = 0;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)  //�����жϣ����յ�һ���ֽ����ݣ�
	{
		Res = USART_ReceiveData(USART2);     //�ѽ��յ����ֽڱ���
	  switch(Res_state)
		{
			case 0:    //'A' Ϊ�ı�ģʽ����/����ASCII��
				if((Res=='A')&& !rxd_flag)  //�ж�֡ͷ && ��ֹ����
				{
					Res_state=1;  //�л�Ϊ��һ��״̬
					rxd_index=0;  //��������0�������´ν��Ž���
				}
				else{
					Res_state=0;  //֡ͷ���ԣ���ѭ��
				}
			  LED0 = 1;   
			break;
			case 1:
				if(Res=='\r')
				{
					Res_state=2;   //������һ��״̬
				}
				else
				{
					rxd_buf[rxd_index] = Res;  //�������������ݴ���BUF
		  	  rxd_index++;    //һ������
				}
				LED0 = 0;  
			 break; 
			case 2:
				if(Res=='\n')
				{
					rxd_flag=1;      //�л���־λ���������ݽ������
					Res_state=0;     //���״̬�������´ν���
				} 
				break;
		}
		
	}
     USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	   //USART_ClearITPendingBit(USART1,USART_IT_IDLE);
  }


void Lora_SendAllInformation(void)
{
	
	//��ʪ��
	//lora_send_buf(TP_Frist_Buf,4);
//	 lora_send_buf(buffer_temp,30);
//	delay_ms(20);
//		lora_send_buf(buffer_hum,30);
//	delay_ms(20);
	lora_send_buf(TP_End_Buf,4);
	
	//GPS��Ϣ
	lora_send_buf(GPS_Frist_Buf,4);
	lora_send_buf(Time_BUF,30);
	delay_ms(200);
	lora_send_buf(GPS_BUF,200);
	delay_ms(400);
	lora_send_buf(GPS_End_Buf,4);
	
	//���յ�ѹ
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


