/*
*********************************************************************************************************
*
*	ģ������ : CO2����ģ��
*	�ļ����� : bsp_CO2.c
*	��    �� : V1.0
*	˵    �� : ��ö�����̼�����������ݲ������ֵ������ʹ�ô���1���գ��������ܵ��ӿ��ؿ��ơ�
            ���������������ܶ�·���������ƣ�����鿴bsp_Modifyregister.c�ļ��о���˵��
*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2024-02-19  ����  ��ʽ����
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
*	�������ƣ�	ComparisonChecksum
*
*	�������ܣ�	�Ա�У����Ƿ���ȷ
							����ͷ�� BYTE0 = 0X42��BYTE1=4D 
							BYTE6 ���ݸ�λ��BYTE7���ݵ�λ����ʾCO2Ũ�ȡ�
							 BYTE15,����У���. BYTE15= BYTE0+BYTE1+����.+BYTE14; 
							 ��: 42 4D 0C 51 09 A2 07 2B 01 35 05 81 20 08 00 AD; 
							CO2Ũ��= BYTE6 X 256 + BYTE7 =07X256 + 2B = 1835;
*
*	��ڲ�����	USARTx��������
*				
*
*	���ز�����	��
*
*	˵����	char sum = 0;		uint8_t sum = 0;  sum�ó��Ľ����һ����
          sum = sum & 0xFF;  ���� sum �����8λ��������λ���㡣 ������û�н������ȷ��
************************************************************
*/
//�Ա�У����Ƿ���ȷ����flag == 0;

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
	// ����У��ͣ�ֻ����ǰ15���ֽ�
    
	 
}

/*
************************************************************
*	�������ƣ�	Calculate_Co2Value
*
*	�������ܣ�	����CO2��ֵ
							
							BYTE6 ���ݸ�λ��BYTE7���ݵ�λ����ʾCO2Ũ�ȡ�
							  
							 ��: 42 4D 0C 51 09 A2 07 2B 01 35 05 81 20 08 00 AD; 
							CO2Ũ��= BYTE6 X 256 + BYTE7 =07X256 + 2B = 1835;
*
*	��ڲ�����	USARTx��������
*				
*
*	���ز�����	��
*
*	˵����	������ΪC8D��һ�����NDIR ���崫���������������ڿ����ж�����̼Ũ�ȵ���
   ����˫ͨ���������̼������ģ�顣�۸�Ϲ󾫶Ƚϸߡ�(50ppm+5%����),
   ���滻Ϊ��JW01-CO2-V2.2 �����źţ��ܱ���
************************************************************
*/

void Calculate_Co2Value(void)
{
  	 uint8_t i;
		 long int  Co2Value=0;
	//	 char Co2ValueString[20];
	// ��ʼλ�ú�Ҫת�����ֽ���
		 uint8_t start = 6;
		 uint8_t length = 2;
	// ʹ�� strtol ������ʮ��������ת��Ϊʮ������
     char *endptr;

    // ����Ҫת�����Ӵ�
    char hexNumber[length * 2 + 1]; // ÿ���ֽ�ռ����ʮ�������ַ����ټ����ַ���������
    for (i = 0; i < length; ++i) {
        sprintf(hexNumber + 2 * i, "%02X", rxd_buf[start + i]);
    }
    hexNumber[length * 2] = '\0'; // ����ַ���������
		
     Co2Value = strtol(hexNumber, &endptr, 16);
		 if (*endptr != '\0') {
        // ������󣬱����¼������Ϣ���ȡ�ʵ��Ĵ�ʩ
        lora_send_Byte(0xFF);
    }
		 
		 // ������
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
*	�� �� ��: LowPower_Calculate_Co2Value
*	����˵��: �͹���ģʽ�¼����ȡCO2��ֵ��ʵ������������ȡ30s
*	��    �Σ���
*	�� �� ֵ: ��
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
