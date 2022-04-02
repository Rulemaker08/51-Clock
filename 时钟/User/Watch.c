#include <INTRINS.H>
#include "AT24C02.h"
#include "Watch.h"
#include "Switch.h"

extern unsigned char time[];
extern Allswitch Switch;

extern unsigned char timeselect;

void TimeShow(unsigned char Mode)
{
	if(Mode==0)
	{
		Nixie_Change(1,time[2]/10);
		Nixie_Change(2,time[2]%10);
		Nixie_Change(3,time[0]%2+12);
		Nixie_Change(4,time[1]/10);
		Nixie_Change(5,time[1]%10);
		Nixie_Change(6,13-time[0]%2);
		Nixie_Change(7,time[0]/10);
		Nixie_Change(8,time[0]%10);
	}
	else
	{
		Nixie_Change(1,time[5]/10);
		Nixie_Change(2,time[5]%10);
		Nixie_Change(3,11);
		Nixie_Change(4,time[4]/10);
		Nixie_Change(5,time[4]%10);
		Nixie_Change(6,11);
		Nixie_Change(7,time[3]/10);
		Nixie_Change(8,time[3]%10);
	}
}

void TimeSet(unsigned char KeyNum)
{
	
	if(KeyNum==5)
	{
		timeselect++;
		if(timeselect==6)
		{
			timeselect=0;
			Switch.ShowMode=0;
		}
	}
	if(KeyNum==6)
	{
		time[timeselect]++;
		
		if(time[0]==60){time[0]=0;}
		if(time[1]==60){time[1]=0;}
		if(time[2]==24){time[2]=0;}
		if(time[5]==100){time[5]=1;}
		if(time[4]==13){time[4]=1;}
		if(timeselect==3)
		{
			if(time[4]==2)
			{
				if(time[5]%4==0)
				{
					if(time[3]==30)
						time[3]=1;
				}
				else
				{
					if(time[3]==29)
						time[3]=1;
				}
			}
			else
			{
				if(time[4]==1||time[4]==3||time[4]==5||time[4]==7||time[4]==8||time[4]==10||time[4]==12)
				{	
					if(time[3]==32)
						time[3]=1;
				}
				if(time[4]==4||time[4]==6||time[4]==9||time[4]==11)
				{	
					if(time[3]==31)
						time[3]=1;
				}
			}
			
		}
		
	}
	if(KeyNum==7)
	{
		time[timeselect]--;
		
		if(time[0]==-1){time[0]=59;}
		if(time[1]==-1){time[1]=59;}
		if(time[2]==-1){time[2]=23;}
		if(time[5]==0){time[5]=99;}
		if(time[4]==0){time[4]=12;}
		if(timeselect==3)
		{
			if(time[4]==2)
			{
				if(time[5]%4==0)
				{
					if(time[3]==0)
						time[3]=29;
				}
				else
				{
					if(time[3]==0)
						time[3]=28;
				}
			}
			else
			{
				if(time[4]==1||time[4]==3||time[4]==5||time[4]==7||time[4]==8||time[4]==10||time[4]==12)
				{	
					if(time[3]==0)
						time[3]=31;
				}
				if(time[4]==4||time[4]==6||time[4]==9||time[4]==11)
				{	
					if(time[3]==0)
						time[3]=30;
				}
			}
		}
	}
	if(KeyNum==9)
	{
		if(timeselect==0||timeselect==1||timeselect==2)
			time[timeselect]=0;
		else 
			time[timeselect]=1;
	}
	TimeTwinkle();
}

void TimeTwinkle()
{
	if(timeselect==0||timeselect==3)
		Switch.SkipNum=3;
	if(timeselect==1||timeselect==4)
		Switch.SkipNum=2;
	if(timeselect==2||timeselect==5)
		Switch.SkipNum=1;
	if(timeselect>=3)
		Switch.ShowMode=1;
}

static void delay(unsigned int a)		//延时10us
{
	while(a--)
	{
		unsigned char i;

		_nop_();
		i = 2;
		while (--i);
	}
}

void TimeKeep(void)
{
	AT24C02_WriteData(3,time[0]);
	delay(100);
	AT24C02_WriteData(4,time[1]);
	delay(100);
	AT24C02_WriteData(5,time[2]);
	delay(100);
	AT24C02_WriteData(6,time[3]);
	delay(100);
	AT24C02_WriteData(7,time[4]);
	delay(100);
	AT24C02_WriteData(8,time[5]);
	delay(100);
}

void TimeRead(void)
{
	time[0]=AT24C02_ReadData(3);
	time[1]=AT24C02_ReadData(4);
	time[2]=AT24C02_ReadData(5);
	time[3]=AT24C02_ReadData(6);
	time[4]=AT24C02_ReadData(7);
	time[5]=AT24C02_ReadData(8);
}