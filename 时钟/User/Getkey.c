#include "Getkey.h"

unsigned char Get_Keynum(void)
{
	static unsigned char keynum1=0,keynum2=0;
	
	keynum1=Key();
	keynum2=MatrixKey();
	
	
	if(keynum2!=4)
	{
		return keynum2;
	}
	if(keynum1!=0)
		return keynum1;
	return 0;
}

void Keynum(unsigned char*keynum)
{
	unsigned char temp=0;
	temp=Get_Keynum();
	
	switch(temp)
	{
		case 0:*keynum=0;break;
		case 1:*keynum=1;break;
		case 2:*keynum=2;break;
		case 3:*keynum=3;break;
		case 4:*keynum=4;break;
		case 5:*keynum=5;break;
		case 6:*keynum=6;break;
		case 7:*keynum=7;break;
		case 8:*keynum=9;break;
		case 20:*keynum=8;break;
		default:break;
	}
}