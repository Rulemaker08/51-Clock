#include "Alarm.h"
#include "Nixie.h"
#include <INTRINS.H>
#include "AT24C02.h"
#include "Switch.h"

extern char time[];
extern Allswitch Switch;
extern unsigned char timeselect;

char AlarmHour,AlarmMinute;

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

static void AlarmTwinkle(void)
{
	if(timeselect==1)
		Switch.SkipNum=3;
	if(timeselect==2)
		Switch.SkipNum=2;
	if(timeselect==3)
		Switch.SkipNum=1;
}	

void AlarmRead(void)
{
	AlarmHour=AT24C02_ReadData(0);
	AlarmMinute=AT24C02_ReadData(1);
	Switch.AlarmFlag=AT24C02_ReadData(2);
}

void AlarmKeep(void)
{
	AT24C02_WriteData(0,AlarmHour);
	delay(100);
	AT24C02_WriteData(1,AlarmMinute);
	delay(100);
	AT24C02_WriteData(2,Switch.AlarmFlag);
	delay(100);
}

void AlarmCheck(void)
{
	if((Switch.AlarmFlag==1)&&(time[1]==AlarmMinute)&&(time[2]==AlarmHour)&&(time[0])==0)
	{
		Switch.BeepFlag=1;
	}
}

void AlarmShow(void)
{
	Nixie_Change(1,AlarmHour/10);
	Nixie_Change(2,AlarmHour%10);
	Nixie_Change(3,13-Switch.AlarmFlag);
	Nixie_Change(4,AlarmMinute/10);
	Nixie_Change(5,AlarmMinute%10);
	Nixie_Change(6,13-Switch.AlarmFlag);
	Nixie_Change(7,Switch.AlarmFlag/10);
	Nixie_Change(8,Switch.AlarmFlag%10);
}

void AlarmSet(unsigned char KeyNum)
{
	
	if(KeyNum==5)
	{
		timeselect++;
		Switch.SkipFlag=1;
		if(timeselect==4)
			timeselect=1;
	}
	if(KeyNum==6)
	{
		if(timeselect==1)
		{
			Switch.AlarmFlag=!Switch.AlarmFlag;
		}
		if(timeselect==2)
		{
			AlarmMinute++;
			if(AlarmMinute>=60)
			{
				AlarmMinute=0;
			}
		}
		if(timeselect==3)
		{
			AlarmHour++;
			if(AlarmHour>=24)
			{
				AlarmHour=0;
			}
		}
	}
	if(KeyNum==7)
	{
		if(timeselect==1)
		{
			Switch.AlarmFlag=!Switch.AlarmFlag;
		}
		if(timeselect==2)
		{
			AlarmMinute--;
			if(AlarmMinute<=-1)
			{
				AlarmMinute=59;
			}
		}
		if(timeselect==3)
		{
			AlarmHour--;
			if(AlarmHour<=-1)
			{
				AlarmHour=23;
			}
		}
	}
	AlarmTwinkle();
}

