/*
*********************************************************************************************************
*
*	ģ������ : ���ڶ�·�����Լ����ӿ��ؿ���
*	�ļ����� : bsp_Modifyregister.c
*	��    �� : V1.2
*	˵    �� : 
*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2023.4.26  ����    usarttest
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
*	�� �� ��: Config_MDPin
*	����˵��: //��ʼ��MD0 MD1���� �� 	PB4\PB5
            //��ʼ������1�ģ�4·����·���ÿ������ţ�USART1_EX_0/USART1_EX_1 : PB3/PA15  
            //��ʼ������2�ģ�2·����·���ÿ������ţ�LORA_EX_EN : PA4
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/	
void Config_MDPin(void)
{
	// ��ʼ��GPIOBʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE ); //���ø���ʱ��
		//GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, DISABLE); //ȫ����SW+JTAG������JTRST��PB4����
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //����SW������JTAG��PA15��PB3��PB4����
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); //��ȫ����SW+JTAG��PA13��PA14��PA15��PB3��PB4����
	
	
		// ����PB4��PB5����Ϊ�������ģʽ
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = USART1_EX_0|LORA_MD0| LORA_MD1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // �������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // GPIO�ٶ�Ϊ50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	  // ����PB4��PB5����Ϊ�������ģʽ
	  GPIO_InitStructure.GPIO_Pin = LORA_EX_EN| USART1_EX_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // �������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // GPIO�ٶ�Ϊ50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    
	// ��PB4��PB5��������͵�ƽ
   
}


/*
*********************************************************************************************************
*	�� �� ��: Config_EnSensorPin
*	����˵��: 
            //��ʼ��GPS\CO2&LANYA\ADC��ص�ѹ������·�ĵ��ӿ������ſ��ƣ�����Lora�ڵ㹦��
             CO2_LANYA_EN :PB0  ADC_DC_EN :PB12  GPS_EN:PA7
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Config_EnSensorPin(void)
{
	// ��ʼ��GPIOBʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE ); //���ø���ʱ��
	  //GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE); //ȫ����SW+JTAG������JTRST��PB4����
	
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //����SW������JTAG��PA15��PB3��PB4����
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); //��ȫ����SW+JTAG��PA13��PA14��PA15��PB3��PB4����
		// ����PB0��PB12����Ϊ�������ģʽ
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = CO2_EN|ADC_DC_EN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // �������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // GPIO�ٶ�Ϊ50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// ����PA7����Ϊ�������ģʽ
   
    GPIO_InitStructure.GPIO_Pin = GPS_EN|LANYA_EN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // �������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // GPIO�ٶ�Ϊ50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/*
*********************************************************************************************************
*	�� �� ��: Reset_MDPin/Set_MDPin/Work_MDPin/Sleeping_MDPin
*	����˵��: �ı�Loraģ����������ţ��������ã�����MD0 MD1 Ϊ�ߵ�ƽ��ģʽΪ�͹���ģʽ
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/	
void Reset_MDPin(void)
{
	 GPIO_ResetBits(GPIOB, GPIO_Pin_4| GPIO_Pin_5);
}




void Set_MDPin(void)
{
	// ��PB4��PB5��������ߵ�ƽ
    GPIO_SetBits(GPIOB, GPIO_Pin_4 | GPIO_Pin_5);
	  delay_ms(20);
}

//��������ģʽ
void Work_MDPin(void)
{
	// ��PB4��PB5��������ߵ�ƽ
    GPIO_SetBits(GPIOB, GPIO_Pin_4 );
	  GPIO_ResetBits(GPIOB,  GPIO_Pin_5);
	  delay_ms(20);
}
//����˯��ģʽ
void Sleeping_MDPin(void)
{
	// ��PB4��PB5��������ߵ�ƽ
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

//�ŵ�20����21����9.6k
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
////	Lora_Send_Buf(Register_Buf,3);//����Ŀǰ��ַ
//	//delay_ms(200);
//	Lora_Send_Buf(Wegister_Buf1,4);//д���µ�ַ
//	delay_ms(20);
//////	Lora_Send_Buf(Reset_Lora,4);//��λģ��
//Set_MDPin();
//	delay_ms(20);
//	Reset_MDPin();
//  Lora_Send_Buf(Register_Buf,3);//�����ı��ĵ�ַ
//	delay_ms(20);
//	Lora_Send_Buf(Wegister_Buf2,4);//д���µ�ַ
//	delay_ms(20);
////	Lora_Send_Buf(Reset_Lora,4);//��λģ��
////	delay_ms(20);
//	Set_MDPin();
//	delay_ms(20);
//	Reset_MDPin();
//	Lora_Send_Buf(Register_Buf,3);//�����ı��ĵ�ַ
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
*	�� �� ��: CO2_LANYA_SensorEN/ADC_DC_EN_SensorEN/GPS_EN_SensorEN
*	����˵��: ����GPS\CO2&LANYA\ADC��ص�ѹ������·�ĵ��ӿ������ſ���
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/	
//����CO2���---------------���ĸ�
void CO2_SensorEN(void)
{
	 GPIO_SetBits(GPIOB, CO2_EN);
}

//������������
void LANYA_SensorEN(void)
{
	 GPIO_SetBits(GPIOA, LANYA_EN);
}

//����ADC��ص�ѹ���---------------���ĸ�
void ADC_DC_EN_SensorEN(void)
{
	 GPIO_SetBits(GPIOB, ADC_DC_EN);
}

//����GPS����ȡ��γ�ȣ����θ߶�---------------���ĸ�
void GPS_EN_SensorEN(void)
{
	 GPIO_SetBits(GPIOA, GPS_EN);
}
//�ر�CO2���---------------���ĸ�
void CO2_SensorCS(void)
{
	 GPIO_ResetBits(GPIOB, CO2_EN);
}

//�رվ�������
void LANYA_SensorCS(void)
{
	 GPIO_ResetBits(GPIOA, LANYA_EN);
}

//�ر�ADC��ص�ѹ���---------------���ĸ�
void ADC_DC_EN_SensorCS(void)
{
	 GPIO_ResetBits(GPIOB, ADC_DC_EN);
}

//�ر�GPS����ȡ��γ�ȣ����θ߶�---------------���ĸ�
void GPS_EN_SensorCS(void)
{
	 GPIO_ResetBits(GPIOA, GPS_EN);
}
/*
*********************************************************************************************************
*	�� �� ��: USART1_Lanya/USART1_CO2/USART1_Printf/USART1_RESERVED
*	����˵��: ����1�ģ�4·����·����,�ı䴮��1�ģ�4·����·�����������ţ��������ã�����MD0 MD1 Ϊ�͵�ƽ����������
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/	
//�л�����Ϊ����
void USART1_Lanya(void)
{
	 GPIO_ResetBits(GPIOB, USART1_EX_0);
	 GPIO_ResetBits(GPIOA, USART1_EX_1);
}

//�л�����CO2
void USART1_CO2(void)
{
	 GPIO_SetBits(GPIOB, USART1_EX_0);
	 GPIO_ResetBits(GPIOA, USART1_EX_1);
}


//�л�����Ϊ��ӡ���
void USART1_Printf(void)
{
	 GPIO_ResetBits(GPIOB, USART1_EX_0);
	 GPIO_SetBits(GPIOA, USART1_EX_1);
}


//�л�����ΪԤ������
void USART1_RESERVED(void)
{
	 GPIO_SetBits(GPIOB, USART1_EX_0);
	 GPIO_SetBits(GPIOA, USART1_EX_1);
}


/*
*********************************************************************************************************
*	�� �� ��: USART2_LORA_EX_EN/USART2_REGLORA_TXD
*	����˵��: ����2�ģ�2·����·����,�ı䴮��2�ģ�2·����·�����������ţ��������ã�����LORA_EX_EN Ϊ�͵�ƽ��
   LORA�������ô���
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
//�л�����ΪLORA��������
void USART2_REGLORA_TXD(void)
{
	 GPIO_SetBits(GPIOA, LORA_EX_EN);
	 
}

//v�л�����ΪLORA�������ô���
void USART2_LORA_EX_EN(void)
{
	 GPIO_ResetBits(GPIOA, LORA_EX_EN);
	 
}

