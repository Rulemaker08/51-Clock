#include <REGX52.H>

sbit K1=P3^1;
sbit K2=P3^0;
sbit K3=P3^2;
sbit K4=P3^3;

char Key_Num;

/**
  * @brief  用户调用函数获取按下的按键的键码值
  * @param  无
  * @retval 键码值
 **/
char Key()
{
	static char Temp;
	Temp=Key_Num;
	Key_Num=0;
	return Temp;
}

/** 
  * @brief  用户读取键码值
  * @param  无
  * @retval 键码值
 **/
char Key_GetNum()
{
	char KeyNum=0;
	
	if(K1==0){KeyNum=1;}
	if(K2==0){KeyNum=2;}
	if(K3==0){KeyNum=3;}
	if(K4==0){KeyNum=4;}
	
	return KeyNum;
}

/**
  * @brief  扫描按键
  * @param  无
  * @retval 扫描结果
 **/
void Key_Check()
{
	static char NowNum,LastNum;
	LastNum=NowNum;
	NowNum=Key_GetNum();
	if(LastNum==1&&NowNum==0)//上一个键码值与现在键码值比较，判断是否按下
	{
		Key_Num=1;
	}
	if(LastNum==2&&NowNum==0)
	{
		Key_Num=2;
	}
	if(LastNum==3&&NowNum==0)
	{
		Key_Num=3;
	}
	if(LastNum==4&&NowNum==0)
	{
		Key_Num=4;
	}
}