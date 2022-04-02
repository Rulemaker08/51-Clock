#include "Nixie.h"
#include "Stopwatch.h"
#include "Switch.h"

extern Allswitch Switch;
extern unsigned char StopSeed;
unsigned char StopMin,StopSec,StopMinsec;

void StopwatchRun(unsigned char keynum)
{
	if(keynum==5)
	{
		Switch.StopwatchFlag=!Switch.StopwatchFlag;
	}
	if(keynum==6||keynum==7)
	{
		StopSeed=0;
		StopMinsec=0;
		StopSec=0;
		StopMinsec=0;
	}
	StopMinsec=StopSeed;
	if(StopMinsec/100)
	{
		StopSec++;
		StopMinsec=0;
	}
	if(StopSec/60)
	{
		StopMin++;
		StopSec=0;
	}
}

void StopwatchShow(void)
{
	Nixie_Change(1,StopMin/10);
	Nixie_Change(2,StopMin%10);
	Nixie_Change(3,11);
	Nixie_Change(4,StopSec/10);
	Nixie_Change(5,StopSec%10);
	Nixie_Change(6,11);
	Nixie_Change(7,StopMinsec/10);
	Nixie_Change(8,StopMinsec%10);
}