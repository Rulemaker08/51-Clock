#include <REGX52.H>

#define second 0x80
#define minute 0x82
#define hour   0x84
#define day    0x86
#define month  0x88
#define year   0x8C
#define week   0x8A
#define WP     0x8E		//写保护

sbit IO=P3^4;
sbit SCLK=P3^6;
sbit CE=P3^5;

//unsigned char time[]={30,6,20,11,12,21,6};//秒，分，时，天，月，年，周几
//char time[]={55,37,17,1,1,22,6};//秒，分，时，天，月，年，周几
extern unsigned char time[];

/**
 * @brief DS1302初始化
 * @param 无
 * @retval 无
 **/
void DS1302_Init()
{
	SCLK=0;
	CE=0;
}

/**
 * @brief DS1302“写”操作
 * @param command 命令/地址
 * @param Data 写入的数据
 * @retval 无
 **/
void DS1302_WriteByte(unsigned char command,unsigned char Data)
{
	int i;
	CE=1;
	for(i=0;i<8;i++)
	{
		IO=command&(0x01<<i);
		SCLK=1;
		SCLK=0;
	}
	for(i=0;i<8;i++)
	{
		IO=Data&(0x01<<i);
		SCLK=1;
		SCLK=0;
	}
	CE=0;
}

/**
 * @brief DS1302“读”操作
 * @param command 命令/地址
 * @retval 读出的数据
 **/
unsigned int DS1302_ReadByte(unsigned char command)
{
	int i,Data=0x00;
	command|=0x01;//将“写”命令改为“读”命令
	CE=1;
	for(i=0;i<8;i++)
	{
		IO=command&(0x01<<i);
		SCLK=0;
		SCLK=1;
	}
	for(i=0;i<8;i++)
	{
		SCLK=1;
		SCLK=0;
		if(IO){Data|=(0x01<<i);}
	}
	CE=0;
	IO=0;
	return Data;
}

/*
	DS1302是以BCD码存储的，所以要将十进制（DEC）转化为BCD码
	DEC=BCD/16*10+BCD%16
	BCD=DEC/10*16+DEC%10
*/

/**
 * @brief BCD与DEC转化函数
 * @param 模式选择 'W':BCD->DEC   'R':DEC->BCD
 * @retval 无
 **/
void Transform(char n)
{
	int i;
	if(n=='W')
	{
		for(i=0;i<7;i++)
		{
			time[i]=time[i]/10*16+time[i]%10;
		}
	}
	if(n=='R')
	{
		for(i=0;i<7;i++)
		{
			time[i]=time[i]/16*10+time[i]%16;
		}
	}
}

/**
 * @brief 将数组写入DS1302中
 * @param 无
 * @retval 无
 **/
void WriteTime()
{
	Transform('W');
	DS1302_WriteByte(WP,0x00);
	DS1302_WriteByte(second,time[0]);
	DS1302_WriteByte(minute,time[1]);
	DS1302_WriteByte(hour,time[2]);
	DS1302_WriteByte(day,time[3]);
	DS1302_WriteByte(month,time[4]);
	DS1302_WriteByte(year,time[5]);
	DS1302_WriteByte(week,time[6]);
}


/**
 * @brief 读DS1302
 * @param 无
 * @retval 无
 **/
void ReadTime()
{
	time[0]=DS1302_ReadByte(second);
	time[1]=DS1302_ReadByte(minute);
	time[2]=DS1302_ReadByte(hour);
	time[3]=DS1302_ReadByte(day);
	time[4]=DS1302_ReadByte(month);
	time[5]=DS1302_ReadByte(year);
	time[6]=DS1302_ReadByte(week);
	Transform('R');
}