/*
*********************************************************************************************************
*
*	ģ������ : �ֽ�ͨ��Э��
*	�ļ����� : bsp_dataanalisis.c
*	��    �� : V1.0
*	˵    �� : �����˴����������ϴ���ʽs��
*

*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2023-08-21  ����  ��ʽ����
*
*	
*
*********************************************************************************************************
*/


#include "bsp.h"
uint8_t SENSOR_DATA_START[1] = {'S'};
uint8_t SENSOR_DATA_END[1] = {'D'};


/*********ȫ�ֱ�������*********/
//�趨��������Ϣ�ϱ��Ļ���
uint8_t SENSOR_DATA_BYTE[248] = {
	FRAME_HEADER_BYTE_1st, FRAME_HEADER_BYTE_2nd, FRAME_HEADER_BYTE_3rd, //֡ͷ�� 3 ���ֽڣ�
	0x13,																 //���������ȣ� 1 ���ֽڣ�
	0x03,																 //����Ϊ���ݣ� 1 ���ֽڣ�
	0x01,																 //Ϊ���������ݣ� 1 ���ֽڣ�
	0x10,																 //���������ݳ��ȣ� 1 ���ֽڣ�
																		 //---- //�������������� 8*N ���ֽڣ��� N ���Ϊ 30��
																		 //- //У�飨 1 ���ֽڣ�
};
uint8_t SENSOR_SAFE_BYTE[248] = {
	FRAME_SHEADER_BYTE_1st, FRAME_SHEADER_BYTE_2nd, FRAME_SHEADER_BYTE_3rd, //֡ͷ��3 ���ֽڣ�
	0x13,																 //���������ȣ�1 ���ֽڣ�
	0x03,																 //����Ϊ���ݣ�1 ���ֽڣ�
	0x01,																 //Ϊ���������ݣ�1 ���ֽڣ�����
	0x10,																 //���������ݳ��ȣ�1 ���ֽڣ�
																		 //---- //��������������8*N ���ֽڣ���N ���Ϊ 30��
																		 //- //У�飨1 ���ֽڣ�
};
_sensorData Sensor_Data_ToFloat; //����������ת��Ϊ������
_sensorData Sensor_Data_To4Byte; //����������ת��Ϊ 4 �ֽ� �ڴ�




/************************************************************************************************
 * �� �� ��: CheckSum
 * ��������: ����У���
 * ��������: uint8_t *buf ��Ҫ����У��͵Ŀ�ʼ�����ַ��uint8_t  len �����ۼӳ����ֽ�
 * �� �� ֵ: checkSum ������У���
 ***********************************************************************************************/
uint8_t CheckSum(uint8_t *buf, uint8_t len)
{
    uint8_t checkSum = 0; //У���
    uint8_t i = 0;

    for (i = 0; i < len; i++)
    {
        checkSum += buf[i];
    }
    return checkSum;
}




/************************************************************************************************
 * �� �� ��: sensor_BasisDate_Upload
 * ��������: ���������ֽ�Э���ϱ�
 * ��������: ����������
 * �� �� ֵ: ��
 ***********************************************************************************************/

void sensor_BasisDate_Upload(void)
{
	
	int8_t i = 0; //ѭ������
	//�����¶ȴ�����
	uint8_t sensor_Temp_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_TEMP_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};
	//����ʪ�ȴ�����
	uint8_t sensor_Humi_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_HUMI_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0,
		0};
		
	//����һ�¹��մ�����
	uint8_t sensor_Lumin_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_LM_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};
			//����CO2������
	uint8_t sensor_CO2_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_CO2_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};
		//����һ��֡β
   	uint8_t sensor_end_buf[8] = {
		ENVIRONMENT_SENSOR_END,ENVIRONMENT_SENSOR_END,ENVIRONMENT_SENSOR_END,
			ENVIRONMENT_SENSOR_END,ENVIRONMENT_SENSOR_END,ENVIRONMENT_SENSOR_END,
			ENVIRONMENT_SENSOR_END,ENVIRONMENT_SENSOR_END
		};
		
		
		//��ֵ��ע��Թ�����ĵĸ�������ֵ------------�¶�---1
	Sensor_Data_To4Byte.f = Temp_value;
	//ע�⣬�ڴ���������С��ģʽ�洢�ģ������Ҫת��Ϊ���ģʽ
	for (i = 0; i < 4; i++)
	{
		sensor_Temp_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
	
	    //��ֵ��ע��Թ�����ĵĸ�������ֵ-----------ʪ��----2
	Sensor_Data_To4Byte.f = Hum_value;
    for (i = 0; i < 4; i++)
	{
		sensor_Humi_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
		//��ֵ��ע��Թ�����ĵĸ�������ֵ------------����----3
	Sensor_Data_To4Byte.f = LT_value;
	//ע�⣬�ڴ���������С��ģʽ�洢�ģ������Ҫת��Ϊ���ģʽ
	for (i = 0; i < 4; i++)
	{
		sensor_Lumin_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
//��ֵ��ע��Թ�����ĵĸ�������ֵ--------------������̼------4
		Sensor_Data_To4Byte.f = CO2_value;
	//ע�⣬�ڴ���������С��ģʽ�洢�ģ������Ҫת��Ϊ���ģʽ
	for (i = 0; i < 4; i++)
	{
		sensor_CO2_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}

	
	//ƫ�Ƶ�ַ 0x03
	SENSOR_DATA_BYTE[DATA_LEN_OFFSET] = 43; //( 1 + 1 + 1 + 5 * 8 )���� 11 �ֽ� ���255
	//ƫ�Ƶ�ַ 0x04
	SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET] = FUN_CODE_DATA; //����֡
	//ƫ�Ƶ�ַ 0x05
	SENSOR_DATA_BYTE[DATA_TYPE_OFFSET] = DATA_TYPE_SENSOR; //����������
	//ƫ�Ƶ�ַ 0x06
	SENSOR_DATA_BYTE[SENSOR_DATA_LEN_OFFSET] = 40; //���� 8 ���ֽ�
	//ƫ�Ƶ�ַ 0x07
	memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (0 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_Temp_buf, 8); //�����¶�����
	memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (1 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_Humi_buf, 8); //����ʪ������
		memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (2 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_Lumin_buf, 8); //������������
	memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (3 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_CO2_buf, 8); //����������̼����
		memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (4 *
													SENSOR_SINGLE_DATA_LEN))],
	     sensor_end_buf, 8); //����֡β
			 
	//����У���
	SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (5*SENSOR_SINGLE_DATA_LEN))] =
		CheckSum(&SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET], SENSOR_DATA_BYTE[DATA_LEN_OFFSET]); //����У����;
	
	USART2_SendData(SENSOR_DATA_BYTE, 48);		//////16+8*4
  
  USART1_SendData(SENSOR_DATA_BYTE, 48);		//////16+8*4
  	
//��������   

}
/************************************************************************************************
 * �� �� ��: sensor_AllDate_Upload
 * ��������: ���������ֽ�Э���ϱ�
 * ��������: ����������
 * �� �� ֵ: ��
 ***********************************************************************************************/

void sensor_AllDate_Upload(void)
{
	
	int8_t i = 0; //ѭ������

	//����һ�µ�ش�����
   	uint8_t sensor_DC_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_DC_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};

		//����һ��γ��
	  uint8_t sensor_latitude_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_latitude_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};
		//����һ�¾���
	  uint8_t sensor_longitude_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_longitude_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};
	//����һ�º��θ߶�
	  uint8_t sensor_altitude_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_altitude_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};
		
	//����һ��֡β
   	uint8_t sensor_end_buf[8] = {
		ENVIRONMENT_SENSOR_END,ENVIRONMENT_SENSOR_END,ENVIRONMENT_SENSOR_END,
		ENVIRONMENT_SENSOR_END,ENVIRONMENT_SENSOR_END,ENVIRONMENT_SENSOR_END,
		ENVIRONMENT_SENSOR_END,ENVIRONMENT_SENSOR_END
		};

	//��ֵ��ע��Թ�����ĵĸ�������ֵ----------------���-----1
	Sensor_Data_To4Byte.f = DC_value;
	//ע�⣬�ڴ���������С��ģʽ�洢�ģ������Ҫת��Ϊ���ģʽ
	for (i = 0; i < 4; i++)
	{
		sensor_DC_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}

		//��ֵ��ע��Թ�����ĵĸ�������ֵ-------------γ��-----2
	Sensor_Data_To4Byte.f = latitude_value;
	//ע�⣬�ڴ���������С��ģʽ�洢�ģ������Ҫת��Ϊ���ģʽ
	for (i = 0; i < 4; i++)
	{
		sensor_latitude_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
	//��ֵ��ע��Թ�����ĵĸ�������ֵ-------------����------3
	Sensor_Data_To4Byte.f = longitude_value;
	//ע�⣬�ڴ���������С��ģʽ�洢�ģ������Ҫת��Ϊ���ģʽ
	for (i = 0; i < 4; i++)
	{
		sensor_longitude_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
	//��ֵ��ע��Թ�����ĵĸ�������ֵ--------------���θ߶�------4
	Sensor_Data_To4Byte.f = altitude_value;
	//ע�⣬�ڴ���������С��ģʽ�洢�ģ������Ҫת��Ϊ���ģʽ
	for (i = 0; i < 4; i++)
	{
		sensor_altitude_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}

	//ƫ�Ƶ�ַ 0x03
	SENSOR_SAFE_BYTE[DATA_LEN_OFFSET] = 43; //( 1 + 1 + 1 + 5 * 8 )���� 11 �ֽ� ���255
	//ƫ�Ƶ�ַ 0x04
	SENSOR_SAFE_BYTE[FRAME_TYPE_OFFSET] = FUN_CODE_DATA; //����֡
	//ƫ�Ƶ�ַ 0x05
	SENSOR_SAFE_BYTE[DATA_TYPE_OFFSET] = DATA_TYPE_SENSOR; //����������
	//ƫ�Ƶ�ַ 0x06
	SENSOR_SAFE_BYTE[SENSOR_DATA_LEN_OFFSET] = 40; //���� 8 ���ֽ�
	//ƫ�Ƶ�ַ 0x07

		memcpy(&SENSOR_SAFE_BYTE[(SENSOR_DATA_START_OFFSET + (0 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_DC_buf, 8); //�����������

			 	memcpy(&SENSOR_SAFE_BYTE[(SENSOR_DATA_START_OFFSET + (1 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_latitude_buf, 8); //����γ������
			  	memcpy(&SENSOR_SAFE_BYTE[(SENSOR_DATA_START_OFFSET + (2 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_longitude_buf, 8); //������������
			  	memcpy(&SENSOR_SAFE_BYTE[(SENSOR_DATA_START_OFFSET + (3 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_altitude_buf, 8); //������������
			 	  memcpy(&SENSOR_SAFE_BYTE[(SENSOR_DATA_START_OFFSET + (4 *
													SENSOR_SINGLE_DATA_LEN))],
	     sensor_end_buf, 8); //����֡β
	//����У���
	SENSOR_SAFE_BYTE[(SENSOR_DATA_START_OFFSET + (5*SENSOR_SINGLE_DATA_LEN))] =
		CheckSum(&SENSOR_SAFE_BYTE[FRAME_TYPE_OFFSET], SENSOR_SAFE_BYTE[DATA_LEN_OFFSET]); //����У����;
	USART2_SendData(SENSOR_SAFE_BYTE, 48);		//////16+4*8
//��������   
	USART1_SendData(SENSOR_SAFE_BYTE, 48);	
}




/************************************************************************************************
 * �� �� ��: sensor_Luminance_Upload
 * ��������: ���ն��ֽ�Э���ϱ�
 * ��������: ���նȸ���������
 * �� �� ֵ: ��
 ***********************************************************************************************/
void sensor_Luminance_Upload(float LT)
{
	int8_t i = 0; //ѭ������
	//����һ�¹��մ�����
	uint8_t sensor_Lumin_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_LM_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};

	//��ֵ��ע��Թ�����ĵĸ�������ֵ
	Sensor_Data_To4Byte.f = LT;
	//ע�⣬�ڴ���������С��ģʽ�洢�ģ������Ҫת��Ϊ���ģʽ
	for (i = 0; i < 4; i++)
	{
		sensor_Lumin_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
	//ƫ�Ƶ�ַ 0x03
	SENSOR_DATA_BYTE[DATA_LEN_OFFSET] = 11; //( 1 + 1 + 1 + 2 * 8 )���� 19 �ֽ�
	//ƫ�Ƶ�ַ 0x04
	SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET] = FUN_CODE_DATA; //����֡
	//ƫ�Ƶ�ַ 0x05
	SENSOR_DATA_BYTE[DATA_TYPE_OFFSET] = DATA_TYPE_SENSOR; //����������
	//ƫ�Ƶ�ַ 0x06
	SENSOR_DATA_BYTE[SENSOR_DATA_LEN_OFFSET] = 8; //���� 16 ���ֽ�
	//ƫ�Ƶ�ַ 0x07
	memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (0 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_Lumin_buf, 8); //������������
	//����У���
	SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (SENSOR_SINGLE_DATA_LEN))] =
		CheckSum(&SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET], SENSOR_DATA_BYTE[DATA_LEN_OFFSET]); //����У����;
	USART2_SendData(SENSOR_DATA_BYTE, 16);												   //��������
}



/************************************************************************************************
 * �� �� ��: sensor_DC_Upload
 * ��������: DC�����ֽ�Э���ϱ�
 * ��������: DC��������
 * �� �� ֵ: ��
 ***********************************************************************************************/
void sensor_DC_Upload(float DC)
{
	int8_t i = 0; //ѭ������
	uint8_t sensor_DC_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_DC_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};

	//��ֵ��ע��Թ�����ĵĸ�������ֵ
	Sensor_Data_To4Byte.f = DC;
	//ע�⣬�ڴ���������С��ģʽ�洢�ģ������Ҫת��Ϊ���ģʽ
	for (i = 0; i < 4; i++)
	{
		sensor_DC_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
	//ƫ�Ƶ�ַ 0x03
	SENSOR_DATA_BYTE[DATA_LEN_OFFSET] = 11; //( 1 + 1 + 1 + 2 * 8 )���� 19 �ֽ�
	//ƫ�Ƶ�ַ 0x04
	SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET] = FUN_CODE_DATA; //����֡
	//ƫ�Ƶ�ַ 0x05
	SENSOR_DATA_BYTE[DATA_TYPE_OFFSET] = DATA_TYPE_SENSOR; //����������
	//ƫ�Ƶ�ַ 0x06
	SENSOR_DATA_BYTE[SENSOR_DATA_LEN_OFFSET] = 8; //���� 16 ���ֽ�
	//ƫ�Ƶ�ַ 0x07
	memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (0 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_DC_buf, 8); //������������
	//����У���
	SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (SENSOR_SINGLE_DATA_LEN))] =
		CheckSum(&SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET], SENSOR_DATA_BYTE[DATA_LEN_OFFSET]); //����У����;
	USART2_SendData(SENSOR_DATA_BYTE, 16);												   //��������
}

///************************************************************************************************
// * �� �� ��: sensor_CO2_Upload
// * ��������: CO2Ũ���ֽ�Э���ϱ�
// * ��������: CO2Ũ����������
// * �� �� ֵ: ��
// ***********************************************************************************************/
//void sensor_CO2_Upload(float CO2)
//{
//	int8_t i = 0; //ѭ������
//	uint8_t sensor_CO2_buf[8] = {
//		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
//		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
//		SENSOR_CO2_CODE,
//		SENSOR_STATUS_RUN,
//		0,
//		0,
//		0, 0};

//	//��ֵ��ע��Թ�����ĵĸ�������ֵ
//	Sensor_Data_To4Byte.f = CO2;
//	//ע�⣬�ڴ���������С��ģʽ�洢�ģ������Ҫת��Ϊ���ģʽ
//	for (i = 0; i < 4; i++)
//	{
//		sensor_CO2_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
//	}
//	//ƫ�Ƶ�ַ 0x03
//	SENSOR_DATA_BYTE[DATA_LEN_OFFSET] = 11; //( 1 + 1 + 1 + 2 * 8 )���� 19 �ֽ�
//	//ƫ�Ƶ�ַ 0x04
//	SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET] = FUN_CODE_DATA; //����֡
//	//ƫ�Ƶ�ַ 0x05
//	SENSOR_DATA_BYTE[DATA_TYPE_OFFSET] = DATA_TYPE_SENSOR; //����������
//	//ƫ�Ƶ�ַ 0x06
//	SENSOR_DATA_BYTE[SENSOR_DATA_LEN_OFFSET] = 8; //���� 16 ���ֽ�
//	//ƫ�Ƶ�ַ 0x07
//	memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (0 *
//														  SENSOR_SINGLE_DATA_LEN))],
//		   sensor_CO2_buf, 8); //������������
//	//����У���
//	SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (SENSOR_SINGLE_DATA_LEN))] =
//		CheckSum(&SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET], SENSOR_DATA_BYTE[DATA_LEN_OFFSET]); //����У����;
//	USART2_SendData(SENSOR_DATA_BYTE, 16);												   //��������
//}


/************************************************************************************************
 * �� �� ��: sensor_TIME_Upload
 * ��������: TIME�ֽ�Э���ϱ�
 * ��������: TIME����������
 * �� �� ֵ: ��
 ***********************************************************************************************/
void sensor_TIME_Upload(void)
{
	int8_t i = 0; //ѭ������
	//����һ�¹��մ�����
	  uint8_t sensor_TIME_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_TIME_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};

	//��ֵ��ע��Թ�����ĵĸ�������ֵ
	Sensor_Data_To4Byte.f = Time_value;
	//ע�⣬�ڴ���������С��ģʽ�洢�ģ������Ҫת��Ϊ���ģʽ
	for (i = 0; i < 4; i++)
	{
		sensor_TIME_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
	//ƫ�Ƶ�ַ 0x03
	SENSOR_DATA_BYTE[DATA_LEN_OFFSET] = 11; //( 1 + 1 + 1 + 2 * 8 )���� 19 �ֽ�
	//ƫ�Ƶ�ַ 0x04
	SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET] = FUN_CODE_DATA; //����֡
	//ƫ�Ƶ�ַ 0x05
	SENSOR_DATA_BYTE[DATA_TYPE_OFFSET] = DATA_TYPE_SENSOR; //����������
	//ƫ�Ƶ�ַ 0x06
	SENSOR_DATA_BYTE[SENSOR_DATA_LEN_OFFSET] = 8; //���� 16 ���ֽ�
	//ƫ�Ƶ�ַ 0x07
	memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (0 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_TIME_buf, 8); //������������
	//����У���
	SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (SENSOR_SINGLE_DATA_LEN))] =
		CheckSum(&SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET], SENSOR_DATA_BYTE[DATA_LEN_OFFSET]); //����У����;
	USART2_SendData(SENSOR_DATA_BYTE, 16);												   //��������
}



/************************************************************************************************
 * �� �� ��: sensor_latitude_Upload
 * ��������: latitude�ֽ�Э���ϱ�
 * ��������: latitude����������
 * �� �� ֵ: ��
 ***********************************************************************************************/
void sensor_latitude_Upload(void)
{
	int8_t i = 0; //ѭ������
	//����һ�¹��մ�����
	uint8_t sensor_latitude_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_latitude_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};

	//��ֵ��ע��Թ�����ĵĸ�������ֵ
	Sensor_Data_To4Byte.f = latitude_value;
	//ע�⣬�ڴ���������С��ģʽ�洢�ģ������Ҫת��Ϊ���ģʽ
	for (i = 0; i < 4; i++)
	{
		sensor_latitude_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
	//ƫ�Ƶ�ַ 0x03
	SENSOR_DATA_BYTE[DATA_LEN_OFFSET] = 11; //( 1 + 1 + 1 + 2 * 8 )���� 19 �ֽ�
	//ƫ�Ƶ�ַ 0x04
	SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET] = FUN_CODE_DATA; //����֡
	//ƫ�Ƶ�ַ 0x05
	SENSOR_DATA_BYTE[DATA_TYPE_OFFSET] = DATA_TYPE_SENSOR; //����������
	//ƫ�Ƶ�ַ 0x06
	SENSOR_DATA_BYTE[SENSOR_DATA_LEN_OFFSET] = 8; //���� 16 ���ֽ�
	//ƫ�Ƶ�ַ 0x07
	memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (0 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_latitude_buf, 8); //������������
	//����У���
	SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (SENSOR_SINGLE_DATA_LEN))] =
		CheckSum(&SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET], SENSOR_DATA_BYTE[DATA_LEN_OFFSET]); //����У����;
	USART2_SendData(SENSOR_DATA_BYTE, 16);												   //��������
}



/************************************************************************************************
 * �� �� ��: sensor_longitude_Upload
 * ��������: longitude�ֽ�Э���ϱ�
 * ��������: longitude����������
 * �� �� ֵ: ��
 ***********************************************************************************************/
void sensor_longitude_Upload(void)
{
	int8_t i = 0; //ѭ������
	//����һ�¹��մ�����
	uint8_t sensor_longitude_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_longitude_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};

	//��ֵ��ע��Թ�����ĵĸ�������ֵ
	Sensor_Data_To4Byte.f = longitude_value;
	//ע�⣬�ڴ���������С��ģʽ�洢�ģ������Ҫת��Ϊ���ģʽ
	for (i = 0; i < 4; i++)
	{
		sensor_longitude_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
	//ƫ�Ƶ�ַ 0x03
	SENSOR_DATA_BYTE[DATA_LEN_OFFSET] = 11; //( 1 + 1 + 1 + 2 * 8 )���� 19 �ֽ�
	//ƫ�Ƶ�ַ 0x04
	SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET] = FUN_CODE_DATA; //����֡
	//ƫ�Ƶ�ַ 0x05
	SENSOR_DATA_BYTE[DATA_TYPE_OFFSET] = DATA_TYPE_SENSOR; //����������
	//ƫ�Ƶ�ַ 0x06
	SENSOR_DATA_BYTE[SENSOR_DATA_LEN_OFFSET] = 8; //���� 16 ���ֽ�
	//ƫ�Ƶ�ַ 0x07
	memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (0 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_longitude_buf, 8); //������������
	//����У���
	SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (SENSOR_SINGLE_DATA_LEN))] =
		CheckSum(&SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET], SENSOR_DATA_BYTE[DATA_LEN_OFFSET]); //����У����;
	USART2_SendData(SENSOR_DATA_BYTE, 16);												   //��������
}


/************************************************************************************************
 * �� �� ��: sensor_altitude_Upload
 * ��������: altitude�ֽ�Э���ϱ�
 * ��������: altitude����������
 * �� �� ֵ: ��
 ***********************************************************************************************/
void sensor_altitude_Upload(void)
{
	int8_t i = 0; //ѭ������
	//����һ�¹��մ�����
	uint8_t sensor_altitude_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_altitude_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};

	//��ֵ��ע��Թ�����ĵĸ�������ֵ
	Sensor_Data_To4Byte.f = altitude_value;
	//ע�⣬�ڴ���������С��ģʽ�洢�ģ������Ҫת��Ϊ���ģʽ
	for (i = 0; i < 4; i++)
	{
		sensor_altitude_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
	//ƫ�Ƶ�ַ 0x03
	SENSOR_DATA_BYTE[DATA_LEN_OFFSET] = 11; //( 1 + 1 + 1 + 2 * 8 )���� 19 �ֽ�
	//ƫ�Ƶ�ַ 0x04
	SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET] = FUN_CODE_DATA; //����֡
	//ƫ�Ƶ�ַ 0x05
	SENSOR_DATA_BYTE[DATA_TYPE_OFFSET] = DATA_TYPE_SENSOR; //����������
	//ƫ�Ƶ�ַ 0x06
	SENSOR_DATA_BYTE[SENSOR_DATA_LEN_OFFSET] = 8; //���� 16 ���ֽ�
	//ƫ�Ƶ�ַ 0x07
	memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (0 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_altitude_buf, 8); //������������
	//����У���
	SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (SENSOR_SINGLE_DATA_LEN))] =
		CheckSum(&SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET], SENSOR_DATA_BYTE[DATA_LEN_OFFSET]); //����У����;
	USART2_SendData(SENSOR_DATA_BYTE, 16);												   //��������
}




