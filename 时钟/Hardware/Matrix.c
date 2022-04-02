#include <REGX52.H>
#include <INTRINS.H>

sbit RCK=P3^5;	//置1写入点阵屏
sbit SCR=P3^6;	//置1下移
sbit SER=P3^4;	//要写入的字节

#define MATRIX_LED_PORT		P0

/**
   *@brief  延时一毫秒@11.0592MHz
   *@param	整形a
   *@retval 无
**/
void delay(unsigned int a)		
{
	while(a--)
	{
		unsigned char i, j;

		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}

/**
  * @brief  点阵屏初始化
  * @param  无
  * @retval 无
  */
//void Matrix_Init()
//{
//	SCR=0;
//	RCK=0;
//}

/**
  * @brief  74HC595写入一个字节
  * @param  Byte 要写入的字节
  * @retval 无
  */
void _74HC595_WriteByte(unsigned char byte)
{
	unsigned char i;
	for (i=0;i<8;i++)
	{
		SER=byte&(0x80>>i);
		SCR=1;
		SCR=0;
	}
	RCK=1;
	RCK=0;
}

/**
  * @brief  LED点阵屏显示一列数据
  * @param  Column 要选择的列，范围：0~7，0在最左边
  * @param  Data 选择列显示的数据，高位在上，1为亮，0为灭
  * @retval 无
  */
void MatrixLED_ShowColumn(unsigned char Column,Data)
{
	_74HC595_WriteByte(Data);
	MATRIX_LED_PORT=~(0x80>>Column);
	delay(1);
	MATRIX_LED_PORT=0xff;
}