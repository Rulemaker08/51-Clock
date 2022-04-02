#include <REGX52.H>

sbit SDA=P2^0;
sbit SCL=P2^1;

/**
  * @brief  I2C开始
  * @param  无
  * @retval 无
 **/
void I2C_Start()
{
	SDA=1;
	SCL=1;
	SDA=0;
	SCL=0;
}

/**
  * @brief  I2C停止
  * @param  无
  * @retval 无
 **/
void I2C_Stop()
{
	SDA=0;
	SCL=1;
	SDA=1;
}

/**
  * @brief  I2C发送一个字节
  * @param  Byte 要发送的数据
  * @retval 无
 **/
void I2C_SendByte(unsigned char Byte)
{
	char i;
	for(i=0;i<8;i++)
	{
		SDA=Byte&(0x80>>i);		//高位在前写入数据
		SCL=1;					//高位发送数据，且不能变化SDA
		SCL=0;					//结束
	}
}

/**
  * @brief  I2C接收数据
  * @param  无
  * @retval Byte 接收的数据
 **/
unsigned char I2C_ReceiveByte()
{
	unsigned char Byte,i;
	SDA=1;							//释放总线
	for(i=0;i<8;i++)
	{
		SCL=1;						//开始读取
		if(SDA)(Byte|=(0x80>>i));	//正式读取
		SCL=0;						//结束
	}
	return Byte;
}

/**
  * @brief  I2C发送应答
  * @param  SA 应答位，0为应答，1为非应答
  * @retval 无
 **/
void I2C_SendAck(unsigned char SA)
{
	SDA=SA;
	SCL=1;
	SCL=0;
}

/**
  * @brief  I2C接收应答位
  * @param  无
  * @retval RA 接收到的应答位，0为应答，1为非应答
 **/
unsigned char I2C_ReceiveAck()
{
	unsigned char RA;
	SDA=1;						//释放总线
	SCL=1;
	RA=SDA;
	SCL=0;
	return RA;
}