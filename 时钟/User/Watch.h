#ifndef __WATCH_H
#define __WATCH_H

#include "DS1302.h"
#include "Nixie.h"


void TimeShow(unsigned char Mode);
void TimeSet(unsigned char KeyNum);
void TimeTwinkle(void);
void TimeRead(void);
void TimeKeep(void);

#endif
