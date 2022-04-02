#ifndef __DS1302_H_
#define __DS1302_H_

//将数组声明为外部可调用


void DS1302_Init();
void DS1302_WriteByte(unsigned char conmmand,unsigned char Data);
unsigned int DS1302_ReadByte(unsigned char conmmand);
void WriteTime();
void ReadTime();

#endif