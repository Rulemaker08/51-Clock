#include <REGX52.H>
#include "I2C.h"

#define 	ADDRESS 	0xA0

/**
  * @brief  AT24C02写入一个字节
  * @param  Address 要写入字节的地址
  * @param  Data 要写入的数据
  * @retval 无
 **/
void AT24C02_WriteData(unsigned char Address,Data)
{
	I2C_Start();
	I2C_SendByte(ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(Address);
	I2C_ReceiveAck();
	I2C_SendByte(Data);
	I2C_ReceiveAck();
	I2C_Stop();
	
}

/**
  * @brief  AT24C02读取一个字节
  * @param  Address 要读出字节的地址
  * @retval  Data 读出的数据
 **/
unsigned char AT24C02_ReadData(unsigned char Address)
{
	unsigned char Data;
	I2C_Start();
	I2C_SendByte(ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(Address);
	I2C_ReceiveAck();
	I2C_Start();
	I2C_SendByte(ADDRESS|0x01);
	I2C_ReceiveAck();
	Data=I2C_ReceiveByte();
	I2C_SendAck(1);
	I2C_Stop();
	return Data;
}