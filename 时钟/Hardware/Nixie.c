#include <REGX52.H>

//暂存数组
unsigned char Nixie_Buf[9]={0};
//数码管字符库
unsigned char nixietable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00,0x40,0x63,0x5C};
//0 1 2 3 4 5 6 7 8 9 ' ' - "口(上)" "口(下)"

/**
  * @brief  用户改变显示值
  * @param  位置 数字
  * @retval 无
 **/
void Nixie_Change(unsigned char Location,Num)
{
	Nixie_Buf[Location]=Num;
}

/**
  * @brief  数码管显示
  * @param  位置 数字
  * @retval 无
 **/
void Nixie(unsigned char Location,num)
{
	P0=0x00;							//段码清0，消影
	switch(Location)
	{
		case 1:P2_4=1;P2_3=1;P2_2=1;break;
		case 2:P2_4=1;P2_3=1;P2_2=0;break;
		case 3:P2_4=1;P2_3=0;P2_2=1;break;
		case 4:P2_4=1;P2_3=0;P2_2=0;break;
		case 5:P2_4=0;P2_3=1;P2_2=1;break;
		case 6:P2_4=0;P2_3=1;P2_2=0;break;
		case 7:P2_4=0;P2_3=0;P2_2=1;break;
		case 8:P2_4=0;P2_3=0;P2_2=0;break;
	}
	P0=nixietable[num];
}

/**
  * @brief  定时显示数码管，需要用在定时器中断函数内
  * @param  无
  * @retval 无
 **/
void Nixie_Show(unsigned char Flag,unsigned char skip)
{
	static char i=1;
	char num=0;
	
	switch(skip)
	{
		case 1:num=1;break;
		case 2:num=4;break;
		case 3:num=7;break;
		default:num=0;break;
	}
	
	if(Flag==1)
	{
		if(i==num||i==num+1)
			goto A;
	}
	Nixie(i,Nixie_Buf[i]);
	A:
	i++;
	if(i>=9)i=1;
	
}
