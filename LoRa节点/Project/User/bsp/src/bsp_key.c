/*
*********************************************************************************************************
*	�� �� ��: bsp_InitKey
*	����˵��: ��ʼ���������ú����� bsp_Init()����
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
#include "bsp.h"

void bsp_InitKey(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	//��һ������GPIOʱ��*
	RCC_APB2PeriphClockCmd(RCC_ALL_KEY,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);/*�ر�jtag,ʹ��SWD,������SWDģʽ����*/
	/*�ڶ������������еİ���GPIO*/
	GPIO_InitStructure.GPIO_Pin =KEY0_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode =KEY0_GPIO_MODE ;
	GPIO_Init(KEY0_GPIO_PORT,&GPIO_InitStructure);
	

	GPIO_InitStructure.GPIO_Pin =WKUP_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode =WKUP_GPIO_MODE ;
	GPIO_Init(WKUP_GPIO_PORT,&GPIO_InitStructure);
	
	
	 

    // ʹ��GPIOBʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // ����PB4����Ϊ�������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // �������ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // �������ٶ�50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure); // ��ʼ��GPIOB

    // ��PB4��������͵�ƽ
    GPIO_ResetBits(GPIOB, GPIO_Pin_4);

}


/*
����KEY_UP������KEY0,KEY1����
KEY_UP  PA0
KEY0    PE4
KEY1    PE3
*/


void EXTIx_Init(void)
{
	//��������IO��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	//��ʼ��io���뺯�����������ǿ����ð�����Ϊ����
  bsp_InitKey();   //�����Ѿ����ƺõİ�������
	
	//����IO�����ж��ߵ�ӳ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
	
	//��ʼ�������жϣ����ô�������
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line1 ;  //PE4ѡ����4
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//ѡ���жϻ����¼�����ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//ѡ���½���
	EXTI_Init(&EXTI_InitStructure);
	
	//�����жϺ����飨NVIC������ʹ��
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��Ϊѡ���ж����ȼ�Ϊ2������ֻ��ѡ0-3��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
	
}
	

void EXTI4_IRQHandler(void)
{
	
		//��д�жϷ�����
	delay_ms(10);     //��ʱ��������
	if(KEY0 == 0)   //�ж��Ƿ���
	{
		LED0 = !LED0;
			bsp_BeepOn();
					bsp_LedToggle(1);
	}
	
	//����ն˱�־λ
	EXTI_ClearFlag(EXTI_Line1);
	
}


