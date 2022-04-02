#include <REGX52.H>

#define key			P1

unsigned char MatrixKey_Num;

unsigned char MatrixKey()
{
	static char Temp;
	Temp=MatrixKey_Num+4;
	MatrixKey_Num=0;
	return Temp;
}

unsigned char MatrixKey_GetNum()
{
	unsigned char KeyNumber=0;
	
	P1=0xFF;
	P1_3=0;
	if(P1_7==0){KeyNumber=1;}
	if(P1_6==0){KeyNumber=5;}
	if(P1_5==0){KeyNumber=9;}
	if(P1_4==0){KeyNumber=13;}
	
	P1=0xFF;
	P1_2=0;
	if(P1_7==0){KeyNumber=2;}
	if(P1_6==0){KeyNumber=6;}
	if(P1_5==0){KeyNumber=10;}
	if(P1_4==0){KeyNumber=14;}
	
	P1=0xFF;
	P1_1=0;
	if(P1_7==0){KeyNumber=3;}
	if(P1_6==0){KeyNumber=7;}
	if(P1_5==0){KeyNumber=11;}
	if(P1_4==0){KeyNumber=15;}
	
	P1=0xFF;
	P1_0=0;
	if(P1_7==0){KeyNumber=4;}
	if(P1_6==0){KeyNumber=8;}
	if(P1_5==0){KeyNumber=12;}
	if(P1_4==0){KeyNumber=16;}
	
	return KeyNumber;
}

void MatrixKey_Check()
{
	static char NowNum,LastNum;
	LastNum=NowNum;
	NowNum=MatrixKey_GetNum();
	if(LastNum==1&&NowNum==0)//上一个键码值与现在键码值比较，判断是否按下
	{
		MatrixKey_Num=1;
	}
	if(LastNum==2&&NowNum==0)
	{
		MatrixKey_Num=2;
	}
	if(LastNum==3&&NowNum==0)
	{
		MatrixKey_Num=3;
	}
	if(LastNum==4&&NowNum==0)
	{
		MatrixKey_Num=4;
	}
	if(LastNum==5&&NowNum==0)//上一个键码值与现在键码值比较，判断是否按下
	{
		MatrixKey_Num=5;
	}
	if(LastNum==6&&NowNum==0)
	{
		MatrixKey_Num=6;
	}
	if(LastNum==7&&NowNum==0)
	{
		MatrixKey_Num=7;
	}
	if(LastNum==8&&NowNum==0)
	{
		MatrixKey_Num=8;
	}
	if(LastNum==9&&NowNum==0)//上一个键码值与现在键码值比较，判断是否按下
	{
		MatrixKey_Num=9;
	}
	if(LastNum==10&&NowNum==0)
	{
		MatrixKey_Num=10;
	}
	if(LastNum==11&&NowNum==0)
	{
		MatrixKey_Num=11;
	}
	if(LastNum==12&&NowNum==0)
	{
		MatrixKey_Num=12;
	}
	if(LastNum==13&&NowNum==0)//上一个键码值与现在键码值比较，判断是否按下
	{
		MatrixKey_Num=13;
	}
	if(LastNum==14&&NowNum==0)
	{
		MatrixKey_Num=14;
	}
	if(LastNum==15&&NowNum==0)
	{
		MatrixKey_Num=15;
	}
	if(LastNum==16&&NowNum==0)
	{
		MatrixKey_Num=16;
	}
}