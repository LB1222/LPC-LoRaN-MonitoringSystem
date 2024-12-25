/*
*********************************************************************************************************
*
*	模块名称 : 字节通信协议
*	文件名称 : bsp_dataanalisis.c
*	版    本 : V1.0
*	说    明 : 定义了传感器数据上传格式s。
*

*
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2023-08-21  刘斌  正式发布
*
*	
*
*********************************************************************************************************
*/


#include "bsp.h"
uint8_t SENSOR_DATA_START[1] = {'S'};
uint8_t SENSOR_DATA_END[1] = {'D'};


/*********全局变量声明*********/
//设定传感器信息上报的缓存
uint8_t SENSOR_DATA_BYTE[248] = {
	FRAME_HEADER_BYTE_1st, FRAME_HEADER_BYTE_2nd, FRAME_HEADER_BYTE_3rd, //帧头（ 3 个字节）
	0x13,																 //数据区长度（ 1 个字节）
	0x03,																 //类型为数据（ 1 个字节）
	0x01,																 //为传感器数据（ 1 个字节）
	0x10,																 //传感器数据长度（ 1 个字节）
																		 //---- //传感器数据区（ 8*N 个字节）（ N 最大为 30）
																		 //- //校验（ 1 个字节）
};
uint8_t SENSOR_SAFE_BYTE[248] = {
	FRAME_SHEADER_BYTE_1st, FRAME_SHEADER_BYTE_2nd, FRAME_SHEADER_BYTE_3rd, //帧头（3 个字节）
	0x13,																 //数据区长度（1 个字节）
	0x03,																 //类型为数据（1 个字节）
	0x01,																 //为传感器数据（1 个字节）安防
	0x10,																 //传感器数据长度（1 个字节）
																		 //---- //传感器数据区（8*N 个字节）（N 最大为 30）
																		 //- //校验（1 个字节）
};
_sensorData Sensor_Data_ToFloat; //传感器数据转换为浮点数
_sensorData Sensor_Data_To4Byte; //传感器数据转换为 4 字节 内存




/************************************************************************************************
 * 函 数 名: CheckSum
 * 函数功能: 计算校验和
 * 函数参数: uint8_t *buf 需要计算校验和的开始数组地址，uint8_t  len 计算累加长度字节
 * 返 回 值: checkSum 计算后的校验和
 ***********************************************************************************************/
uint8_t CheckSum(uint8_t *buf, uint8_t len)
{
    uint8_t checkSum = 0; //校验和
    uint8_t i = 0;

    for (i = 0; i < len; i++)
    {
        checkSum += buf[i];
    }
    return checkSum;
}




/************************************************************************************************
 * 函 数 名: sensor_BasisDate_Upload
 * 函数功能: 基本数据字节协议上报
 * 函数参数: 浮点数数据
 * 返 回 值: 无
 ***********************************************************************************************/

void sensor_BasisDate_Upload(void)
{
	
	int8_t i = 0; //循环数据
	//定义温度传感器
	uint8_t sensor_Temp_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_TEMP_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};
	//定义湿度传感器
	uint8_t sensor_Humi_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_HUMI_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0,
		0};
		
	//定义一下光照传感器
	uint8_t sensor_Lumin_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_LM_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};
			//定义CO2传感器
	uint8_t sensor_CO2_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_CO2_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};
		//定义一下帧尾
   	uint8_t sensor_end_buf[8] = {
		ENVIRONMENT_SENSOR_END,ENVIRONMENT_SENSOR_END,ENVIRONMENT_SENSOR_END,
			ENVIRONMENT_SENSOR_END,ENVIRONMENT_SENSOR_END,ENVIRONMENT_SENSOR_END,
			ENVIRONMENT_SENSOR_END,ENVIRONMENT_SENSOR_END
		};
		
		
		//赋值，注意对共用体的的浮点数赋值------------温度---1
	Sensor_Data_To4Byte.f = Temp_value;
	//注意，内存中数组是小端模式存储的，因此需要转换为大端模式
	for (i = 0; i < 4; i++)
	{
		sensor_Temp_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
	
	    //赋值，注意对共用体的的浮点数赋值-----------湿度----2
	Sensor_Data_To4Byte.f = Hum_value;
    for (i = 0; i < 4; i++)
	{
		sensor_Humi_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
		//赋值，注意对共用体的的浮点数赋值------------光照----3
	Sensor_Data_To4Byte.f = LT_value;
	//注意，内存中数组是小端模式存储的，因此需要转换为大端模式
	for (i = 0; i < 4; i++)
	{
		sensor_Lumin_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
//赋值，注意对共用体的的浮点数赋值--------------二氧化碳------4
		Sensor_Data_To4Byte.f = CO2_value;
	//注意，内存中数组是小端模式存储的，因此需要转换为大端模式
	for (i = 0; i < 4; i++)
	{
		sensor_CO2_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}

	
	//偏移地址 0x03
	SENSOR_DATA_BYTE[DATA_LEN_OFFSET] = 43; //( 1 + 1 + 1 + 5 * 8 )长度 11 字节 最大255
	//偏移地址 0x04
	SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET] = FUN_CODE_DATA; //数据帧
	//偏移地址 0x05
	SENSOR_DATA_BYTE[DATA_TYPE_OFFSET] = DATA_TYPE_SENSOR; //传感器数据
	//偏移地址 0x06
	SENSOR_DATA_BYTE[SENSOR_DATA_LEN_OFFSET] = 40; //长度 8 个字节
	//偏移地址 0x07
	memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (0 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_Temp_buf, 8); //拷贝温度数据
	memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (1 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_Humi_buf, 8); //拷贝湿度数据
		memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (2 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_Lumin_buf, 8); //拷贝光照数据
	memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (3 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_CO2_buf, 8); //拷贝二氧化碳数据
		memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (4 *
													SENSOR_SINGLE_DATA_LEN))],
	     sensor_end_buf, 8); //拷贝帧尾
			 
	//计算校验和
	SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (5*SENSOR_SINGLE_DATA_LEN))] =
		CheckSum(&SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET], SENSOR_DATA_BYTE[DATA_LEN_OFFSET]); //计算校验码;
	
	USART2_SendData(SENSOR_DATA_BYTE, 48);		//////16+8*4
  
  USART1_SendData(SENSOR_DATA_BYTE, 48);		//////16+8*4
  	
//发送数据   

}
/************************************************************************************************
 * 函 数 名: sensor_AllDate_Upload
 * 函数功能: 所有数据字节协议上报
 * 函数参数: 浮点数数据
 * 返 回 值: 无
 ***********************************************************************************************/

void sensor_AllDate_Upload(void)
{
	
	int8_t i = 0; //循环数据

	//定义一下电池传感器
   	uint8_t sensor_DC_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_DC_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};

		//定义一下纬度
	  uint8_t sensor_latitude_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_latitude_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};
		//定义一下经度
	  uint8_t sensor_longitude_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_longitude_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};
	//定义一下海拔高度
	  uint8_t sensor_altitude_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_altitude_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};
		
	//定义一下帧尾
   	uint8_t sensor_end_buf[8] = {
		ENVIRONMENT_SENSOR_END,ENVIRONMENT_SENSOR_END,ENVIRONMENT_SENSOR_END,
		ENVIRONMENT_SENSOR_END,ENVIRONMENT_SENSOR_END,ENVIRONMENT_SENSOR_END,
		ENVIRONMENT_SENSOR_END,ENVIRONMENT_SENSOR_END
		};

	//赋值，注意对共用体的的浮点数赋值----------------电池-----1
	Sensor_Data_To4Byte.f = DC_value;
	//注意，内存中数组是小端模式存储的，因此需要转换为大端模式
	for (i = 0; i < 4; i++)
	{
		sensor_DC_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}

		//赋值，注意对共用体的的浮点数赋值-------------纬度-----2
	Sensor_Data_To4Byte.f = latitude_value;
	//注意，内存中数组是小端模式存储的，因此需要转换为大端模式
	for (i = 0; i < 4; i++)
	{
		sensor_latitude_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
	//赋值，注意对共用体的的浮点数赋值-------------经度------3
	Sensor_Data_To4Byte.f = longitude_value;
	//注意，内存中数组是小端模式存储的，因此需要转换为大端模式
	for (i = 0; i < 4; i++)
	{
		sensor_longitude_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
	//赋值，注意对共用体的的浮点数赋值--------------海拔高度------4
	Sensor_Data_To4Byte.f = altitude_value;
	//注意，内存中数组是小端模式存储的，因此需要转换为大端模式
	for (i = 0; i < 4; i++)
	{
		sensor_altitude_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}

	//偏移地址 0x03
	SENSOR_SAFE_BYTE[DATA_LEN_OFFSET] = 43; //( 1 + 1 + 1 + 5 * 8 )长度 11 字节 最大255
	//偏移地址 0x04
	SENSOR_SAFE_BYTE[FRAME_TYPE_OFFSET] = FUN_CODE_DATA; //数据帧
	//偏移地址 0x05
	SENSOR_SAFE_BYTE[DATA_TYPE_OFFSET] = DATA_TYPE_SENSOR; //传感器数据
	//偏移地址 0x06
	SENSOR_SAFE_BYTE[SENSOR_DATA_LEN_OFFSET] = 40; //长度 8 个字节
	//偏移地址 0x07

		memcpy(&SENSOR_SAFE_BYTE[(SENSOR_DATA_START_OFFSET + (0 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_DC_buf, 8); //拷贝电池数据

			 	memcpy(&SENSOR_SAFE_BYTE[(SENSOR_DATA_START_OFFSET + (1 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_latitude_buf, 8); //拷贝纬度数据
			  	memcpy(&SENSOR_SAFE_BYTE[(SENSOR_DATA_START_OFFSET + (2 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_longitude_buf, 8); //拷贝经度数据
			  	memcpy(&SENSOR_SAFE_BYTE[(SENSOR_DATA_START_OFFSET + (3 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_altitude_buf, 8); //拷贝海拔数据
			 	  memcpy(&SENSOR_SAFE_BYTE[(SENSOR_DATA_START_OFFSET + (4 *
													SENSOR_SINGLE_DATA_LEN))],
	     sensor_end_buf, 8); //拷贝帧尾
	//计算校验和
	SENSOR_SAFE_BYTE[(SENSOR_DATA_START_OFFSET + (5*SENSOR_SINGLE_DATA_LEN))] =
		CheckSum(&SENSOR_SAFE_BYTE[FRAME_TYPE_OFFSET], SENSOR_SAFE_BYTE[DATA_LEN_OFFSET]); //计算校验码;
	USART2_SendData(SENSOR_SAFE_BYTE, 48);		//////16+4*8
//发送数据   
	USART1_SendData(SENSOR_SAFE_BYTE, 48);	
}




/************************************************************************************************
 * 函 数 名: sensor_Luminance_Upload
 * 函数功能: 光照度字节协议上报
 * 函数参数: 光照度浮点数数据
 * 返 回 值: 无
 ***********************************************************************************************/
void sensor_Luminance_Upload(float LT)
{
	int8_t i = 0; //循环数据
	//定义一下光照传感器
	uint8_t sensor_Lumin_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_LM_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};

	//赋值，注意对共用体的的浮点数赋值
	Sensor_Data_To4Byte.f = LT;
	//注意，内存中数组是小端模式存储的，因此需要转换为大端模式
	for (i = 0; i < 4; i++)
	{
		sensor_Lumin_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
	//偏移地址 0x03
	SENSOR_DATA_BYTE[DATA_LEN_OFFSET] = 11; //( 1 + 1 + 1 + 2 * 8 )长度 19 字节
	//偏移地址 0x04
	SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET] = FUN_CODE_DATA; //数据帧
	//偏移地址 0x05
	SENSOR_DATA_BYTE[DATA_TYPE_OFFSET] = DATA_TYPE_SENSOR; //传感器数据
	//偏移地址 0x06
	SENSOR_DATA_BYTE[SENSOR_DATA_LEN_OFFSET] = 8; //长度 16 个字节
	//偏移地址 0x07
	memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (0 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_Lumin_buf, 8); //拷贝光照数据
	//计算校验和
	SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (SENSOR_SINGLE_DATA_LEN))] =
		CheckSum(&SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET], SENSOR_DATA_BYTE[DATA_LEN_OFFSET]); //计算校验码;
	USART2_SendData(SENSOR_DATA_BYTE, 16);												   //发送数据
}



/************************************************************************************************
 * 函 数 名: sensor_DC_Upload
 * 函数功能: DC数据字节协议上报
 * 函数参数: DC整数数据
 * 返 回 值: 无
 ***********************************************************************************************/
void sensor_DC_Upload(float DC)
{
	int8_t i = 0; //循环数据
	uint8_t sensor_DC_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_DC_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};

	//赋值，注意对共用体的的浮点数赋值
	Sensor_Data_To4Byte.f = DC;
	//注意，内存中数组是小端模式存储的，因此需要转换为大端模式
	for (i = 0; i < 4; i++)
	{
		sensor_DC_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
	//偏移地址 0x03
	SENSOR_DATA_BYTE[DATA_LEN_OFFSET] = 11; //( 1 + 1 + 1 + 2 * 8 )长度 19 字节
	//偏移地址 0x04
	SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET] = FUN_CODE_DATA; //数据帧
	//偏移地址 0x05
	SENSOR_DATA_BYTE[DATA_TYPE_OFFSET] = DATA_TYPE_SENSOR; //传感器数据
	//偏移地址 0x06
	SENSOR_DATA_BYTE[SENSOR_DATA_LEN_OFFSET] = 8; //长度 16 个字节
	//偏移地址 0x07
	memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (0 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_DC_buf, 8); //拷贝光照数据
	//计算校验和
	SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (SENSOR_SINGLE_DATA_LEN))] =
		CheckSum(&SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET], SENSOR_DATA_BYTE[DATA_LEN_OFFSET]); //计算校验码;
	USART2_SendData(SENSOR_DATA_BYTE, 16);												   //发送数据
}

///************************************************************************************************
// * 函 数 名: sensor_CO2_Upload
// * 函数功能: CO2浓度字节协议上报
// * 函数参数: CO2浓度整数数据
// * 返 回 值: 无
// ***********************************************************************************************/
//void sensor_CO2_Upload(float CO2)
//{
//	int8_t i = 0; //循环数据
//	uint8_t sensor_CO2_buf[8] = {
//		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
//		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
//		SENSOR_CO2_CODE,
//		SENSOR_STATUS_RUN,
//		0,
//		0,
//		0, 0};

//	//赋值，注意对共用体的的浮点数赋值
//	Sensor_Data_To4Byte.f = CO2;
//	//注意，内存中数组是小端模式存储的，因此需要转换为大端模式
//	for (i = 0; i < 4; i++)
//	{
//		sensor_CO2_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
//	}
//	//偏移地址 0x03
//	SENSOR_DATA_BYTE[DATA_LEN_OFFSET] = 11; //( 1 + 1 + 1 + 2 * 8 )长度 19 字节
//	//偏移地址 0x04
//	SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET] = FUN_CODE_DATA; //数据帧
//	//偏移地址 0x05
//	SENSOR_DATA_BYTE[DATA_TYPE_OFFSET] = DATA_TYPE_SENSOR; //传感器数据
//	//偏移地址 0x06
//	SENSOR_DATA_BYTE[SENSOR_DATA_LEN_OFFSET] = 8; //长度 16 个字节
//	//偏移地址 0x07
//	memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (0 *
//														  SENSOR_SINGLE_DATA_LEN))],
//		   sensor_CO2_buf, 8); //拷贝光照数据
//	//计算校验和
//	SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (SENSOR_SINGLE_DATA_LEN))] =
//		CheckSum(&SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET], SENSOR_DATA_BYTE[DATA_LEN_OFFSET]); //计算校验码;
//	USART2_SendData(SENSOR_DATA_BYTE, 16);												   //发送数据
//}


/************************************************************************************************
 * 函 数 名: sensor_TIME_Upload
 * 函数功能: TIME字节协议上报
 * 函数参数: TIME浮点数数据
 * 返 回 值: 无
 ***********************************************************************************************/
void sensor_TIME_Upload(void)
{
	int8_t i = 0; //循环数据
	//定义一下光照传感器
	  uint8_t sensor_TIME_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_TIME_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};

	//赋值，注意对共用体的的浮点数赋值
	Sensor_Data_To4Byte.f = Time_value;
	//注意，内存中数组是小端模式存储的，因此需要转换为大端模式
	for (i = 0; i < 4; i++)
	{
		sensor_TIME_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
	//偏移地址 0x03
	SENSOR_DATA_BYTE[DATA_LEN_OFFSET] = 11; //( 1 + 1 + 1 + 2 * 8 )长度 19 字节
	//偏移地址 0x04
	SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET] = FUN_CODE_DATA; //数据帧
	//偏移地址 0x05
	SENSOR_DATA_BYTE[DATA_TYPE_OFFSET] = DATA_TYPE_SENSOR; //传感器数据
	//偏移地址 0x06
	SENSOR_DATA_BYTE[SENSOR_DATA_LEN_OFFSET] = 8; //长度 16 个字节
	//偏移地址 0x07
	memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (0 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_TIME_buf, 8); //拷贝光照数据
	//计算校验和
	SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (SENSOR_SINGLE_DATA_LEN))] =
		CheckSum(&SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET], SENSOR_DATA_BYTE[DATA_LEN_OFFSET]); //计算校验码;
	USART2_SendData(SENSOR_DATA_BYTE, 16);												   //发送数据
}



/************************************************************************************************
 * 函 数 名: sensor_latitude_Upload
 * 函数功能: latitude字节协议上报
 * 函数参数: latitude浮点数数据
 * 返 回 值: 无
 ***********************************************************************************************/
void sensor_latitude_Upload(void)
{
	int8_t i = 0; //循环数据
	//定义一下光照传感器
	uint8_t sensor_latitude_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_latitude_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};

	//赋值，注意对共用体的的浮点数赋值
	Sensor_Data_To4Byte.f = latitude_value;
	//注意，内存中数组是小端模式存储的，因此需要转换为大端模式
	for (i = 0; i < 4; i++)
	{
		sensor_latitude_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
	//偏移地址 0x03
	SENSOR_DATA_BYTE[DATA_LEN_OFFSET] = 11; //( 1 + 1 + 1 + 2 * 8 )长度 19 字节
	//偏移地址 0x04
	SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET] = FUN_CODE_DATA; //数据帧
	//偏移地址 0x05
	SENSOR_DATA_BYTE[DATA_TYPE_OFFSET] = DATA_TYPE_SENSOR; //传感器数据
	//偏移地址 0x06
	SENSOR_DATA_BYTE[SENSOR_DATA_LEN_OFFSET] = 8; //长度 16 个字节
	//偏移地址 0x07
	memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (0 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_latitude_buf, 8); //拷贝光照数据
	//计算校验和
	SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (SENSOR_SINGLE_DATA_LEN))] =
		CheckSum(&SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET], SENSOR_DATA_BYTE[DATA_LEN_OFFSET]); //计算校验码;
	USART2_SendData(SENSOR_DATA_BYTE, 16);												   //发送数据
}



/************************************************************************************************
 * 函 数 名: sensor_longitude_Upload
 * 函数功能: longitude字节协议上报
 * 函数参数: longitude浮点数数据
 * 返 回 值: 无
 ***********************************************************************************************/
void sensor_longitude_Upload(void)
{
	int8_t i = 0; //循环数据
	//定义一下光照传感器
	uint8_t sensor_longitude_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_longitude_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};

	//赋值，注意对共用体的的浮点数赋值
	Sensor_Data_To4Byte.f = longitude_value;
	//注意，内存中数组是小端模式存储的，因此需要转换为大端模式
	for (i = 0; i < 4; i++)
	{
		sensor_longitude_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
	//偏移地址 0x03
	SENSOR_DATA_BYTE[DATA_LEN_OFFSET] = 11; //( 1 + 1 + 1 + 2 * 8 )长度 19 字节
	//偏移地址 0x04
	SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET] = FUN_CODE_DATA; //数据帧
	//偏移地址 0x05
	SENSOR_DATA_BYTE[DATA_TYPE_OFFSET] = DATA_TYPE_SENSOR; //传感器数据
	//偏移地址 0x06
	SENSOR_DATA_BYTE[SENSOR_DATA_LEN_OFFSET] = 8; //长度 16 个字节
	//偏移地址 0x07
	memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (0 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_longitude_buf, 8); //拷贝光照数据
	//计算校验和
	SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (SENSOR_SINGLE_DATA_LEN))] =
		CheckSum(&SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET], SENSOR_DATA_BYTE[DATA_LEN_OFFSET]); //计算校验码;
	USART2_SendData(SENSOR_DATA_BYTE, 16);												   //发送数据
}


/************************************************************************************************
 * 函 数 名: sensor_altitude_Upload
 * 函数功能: altitude字节协议上报
 * 函数参数: altitude浮点数数据
 * 返 回 值: 无
 ***********************************************************************************************/
void sensor_altitude_Upload(void)
{
	int8_t i = 0; //循环数据
	//定义一下光照传感器
	uint8_t sensor_altitude_buf[8] = {
		ENVIRONMENT_SENSOR_TYPE_CODE_MSB,
		ENVIRONMENT_SENSOR_TYPE_CODE_LSB,
		SENSOR_altitude_CODE,
		SENSOR_STATUS_RUN,
		0,
		0,
		0, 0};

	//赋值，注意对共用体的的浮点数赋值
	Sensor_Data_To4Byte.f = altitude_value;
	//注意，内存中数组是小端模式存储的，因此需要转换为大端模式
	for (i = 0; i < 4; i++)
	{
		sensor_altitude_buf[4 + i] = Sensor_Data_To4Byte.x[3 - i];
	}
	//偏移地址 0x03
	SENSOR_DATA_BYTE[DATA_LEN_OFFSET] = 11; //( 1 + 1 + 1 + 2 * 8 )长度 19 字节
	//偏移地址 0x04
	SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET] = FUN_CODE_DATA; //数据帧
	//偏移地址 0x05
	SENSOR_DATA_BYTE[DATA_TYPE_OFFSET] = DATA_TYPE_SENSOR; //传感器数据
	//偏移地址 0x06
	SENSOR_DATA_BYTE[SENSOR_DATA_LEN_OFFSET] = 8; //长度 16 个字节
	//偏移地址 0x07
	memcpy(&SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (0 *
														  SENSOR_SINGLE_DATA_LEN))],
		   sensor_altitude_buf, 8); //拷贝光照数据
	//计算校验和
	SENSOR_DATA_BYTE[(SENSOR_DATA_START_OFFSET + (SENSOR_SINGLE_DATA_LEN))] =
		CheckSum(&SENSOR_DATA_BYTE[FRAME_TYPE_OFFSET], SENSOR_DATA_BYTE[DATA_LEN_OFFSET]); //计算校验码;
	USART2_SendData(SENSOR_DATA_BYTE, 16);												   //发送数据
}




