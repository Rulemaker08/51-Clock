#include <REGX52.H>
#include "Switch.h"
#include "Getkey.h"
#include "Timer.h"
#include "Matrix.h"
#include "Watch.h"
#include "Alarm.h"
#include "Stopwatch.h"

Allswitch Switch={2,3,0,0,0,0};

unsigned char time[]={0,0,0,0,0,0,6};
unsigned char Smiley[]={0x3C,0x42,0xA9,0x85,0x85,0xA9,0x42,0x3C};		//笑脸符

typedef struct 
{
	unsigned PictureFlag:1;
	unsigned Flag:2;
	unsigned :1;
	unsigned i:4;
}Picture;

Picture picture={0,0,0};

unsigned char mode=0;
unsigned char flag=0;
unsigned int i=0;
unsigned char StopSeed;
unsigned char timeselect;

void TellTime(unsigned char*mode);

int main(void)
{
	unsigned char keynum=0;
	Timer_Init();
	DS1302_Init();
	TimeRead();
	AlarmRead();
	
	
	if(time[3]==0)
		time[3]=1;
	if(time[4]==0)
		time[4]=1;
	if(time[5]==0)
		time[5]=1;
	WriteTime();
	while(1)
	{
		Keynum(&keynum);
		if(keynum==1)
		{
			if(Switch.BeepFlag==0)
			{
				StopSeed=0;
				Switch.ShowMode=!Switch.ShowMode;
				flag=1;
			}
			Switch.BeepFlag=0;
		}
		else if(keynum==2)
		{
			
			if(mode==0&&Switch.BeepFlag==0)
			{
				mode=1;
				Switch.SkipFlag=1;
				timeselect=0;
			}
			else if(mode==1)
			{
				mode=0;
				WriteTime();
				Switch.ShowMode=0;
				timeselect=0;
				Switch.SkipFlag=2;
				Switch.SkipNum=3;
			}
			Switch.BeepFlag=0;
		}
		else if(keynum==3)
		{
			if(mode==0&&Switch.BeepFlag==0)
			{
				mode=2;
				Switch.SkipNum=3;
				timeselect=0;
			}
			else if(mode==2)
			{
				mode=0;
				timeselect=0;
				Switch.SkipFlag=2;
			}
			Switch.BeepFlag=0;
		}
		else if(keynum==4)
		{
			
			if(mode==0&&Switch.BeepFlag==0)
			{
				mode=3;
			}
			else if(mode==3)
			{
				mode=0;
				Switch.StopwatchFlag=0;
			}
			Switch.BeepFlag=0;
		}
		else if(keynum==8)
		{
			
			if(mode==0&&Switch.BeepFlag==0)
			{
				mode=4;
				TR1=0;
				ET1=0;
				TimeKeep();
				AlarmKeep();
			}
			else if(mode==4)
			{
				mode=0;
				picture.PictureFlag=0;
				TR1=1;
				ET1=1;
			}
			Switch.BeepFlag=0;
			
		}
		
		switch(mode)
		{
			case 0:
			{
				
				StopSeed=0;
				ReadTime();
				TellTime(&mode);
				TimeShow(Switch.ShowMode);
				AlarmCheck();
				
				break;
			}
			case 1:TimeSet(keynum);TimeShow(Switch.ShowMode);break;
			case 2:AlarmSet(keynum);AlarmShow();break;
			case 3:StopwatchRun(keynum);StopwatchShow();break;
			case 4:picture.PictureFlag=1;Switch.StopwatchFlag=1;if(i!=0){TellTime(&mode);}break;
		}
		
		
		
	}
}

void Timer0_Rountine(void)		interrupt 1		//扫描专用
{
	static unsigned char counter1=0,counter3=0,counter4=0;
	static unsigned int counter2=0,counter5=0;
	
	TL0 = (65536-100)%256;		//设置定时0初值
	TH0 = (65536-100)/256;		//设置定时0初值
	
	counter1++;
	if(counter1>=200)
	{
		Key_Check();
		MatrixKey_Check();
		counter1=0;
	}
	
	counter2++;
	if(counter2>=10)
	{
		if(Switch.BeepFlag==1)
		{
			P2_5=!P2_5;
		}
		counter2=0;
	}
	
	counter3++;
	if(counter3>=100)
	{
		counter3=0;
		if(Switch.StopwatchFlag)
		{
			StopSeed++;
			StopSeed%=101;
		}
	}
	
	counter4++;
	if(counter4>=10)
	{
		if(picture.PictureFlag==1)
		{
			MatrixLED_ShowColumn(picture.i,Smiley[picture.i]);
			picture.i++;
			picture.i%=8;
		}
		counter4=0;
	}
	
	if(flag==1)
	{
		counter5++;
		if(counter5>=25000)
		{
			Switch.ShowMode=0;
			flag=0;
			counter5=0;
		}
	}
}

void Timer1_Rountine(void)		interrupt 3		//显示专用
{
	static unsigned char counter1=0;
	static unsigned int counter2=0;
	TL1 = (65536-10)%256;		//设置定时1初值
	TH1 = (65536-10)/256;		//设置定时1初值
	
	counter1++;
	if(counter1>=5)
	{
		Nixie_Show(Switch.SkipFlag,Switch.SkipNum);
		counter1=0;
	}
	
	counter2++;
	if(counter2>=2000)
	{
		if(Switch.SkipFlag!=2)
			Switch.SkipFlag=!Switch.SkipFlag;
		counter2=0;
	}
}

void TellTime(unsigned char *mode)
{
	
	
	if(time[1]==0&&i==0)//只有i==0时才判断
	{
		i=2;
		picture.Flag=1;
		if((time[2]>=6)&&(time[2]<=22))
			picture.Flag=2;
	}
	if(time[1]!=0)//只有分钟不满足时，才复位i，防止重复判断
	{
		i=0;
		picture.Flag=0;
	}
		
	
	if(StopSeed>=50)
	{
		i++;
		if(i>=100)
		{
			if(i==2)
				i=3;
			picture.Flag=1;
			if(i>=3000)
			{
				picture.Flag=0;
			}
		}
	}
	if(picture.Flag==1)
	{
		ET1=0;
		TR1=0;
		*mode=4;
		Switch.BeepFlag=0;
	}
	else if(picture.Flag==2)
	{
		ET1=0;
		TR1=0;
		*mode=4;			
		Switch.BeepFlag=1;
	}
	else
	{
		TR1=1;
		ET1=1;
		Switch.StopwatchFlag=0;
		picture.PictureFlag=0;
		Switch.BeepFlag=0;
		*mode=0;
	}
}
