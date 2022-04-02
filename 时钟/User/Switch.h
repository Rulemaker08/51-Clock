#ifndef __SWITCH_H
#define __SWITCH_H

typedef struct 
{
	unsigned SkipFlag:2;
	unsigned SkipNum: 2;
	unsigned ShowMode:1;
	unsigned AlarmFlag:1;
	unsigned BeepFlag:1;
	unsigned StopwatchFlag:1;
}Allswitch;

#endif
