#include <REGX52.H>
#include "INTRINS.H"
#include "AT24C02.h"

void delay(unsigned int a)		//延时10us
{
	while(a--)
	{
		unsigned char i;

		_nop_();
		i = 2;
		while (--i);
	}
}

int main(void)
{
	AT24C02_WriteData(0,0);
	delay(100);
	AT24C02_WriteData(1,0);
	delay(100);
	AT24C02_WriteData(2,0);
	delay(100);
	AT24C02_WriteData(3,0);
	delay(100);
	AT24C02_WriteData(4,0);
	delay(100);
	AT24C02_WriteData(5,0);
	delay(100);
	AT24C02_WriteData(6,0);
	delay(100);
	AT24C02_WriteData(7,0);
	delay(100);
	AT24C02_WriteData(8,0);
	delay(100);
	
	return 0;
}