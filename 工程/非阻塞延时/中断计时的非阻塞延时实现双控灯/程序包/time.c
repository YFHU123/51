#include "time.h"

unsigned int time1_cnt;
unsigned char time1_flag;
unsigned time1_enable;

unsigned int time2_cnt;
unsigned char time2_flag;
unsigned time2_enable;

void Timer0Init(void)		//1??@12.000MHz
{
	TMOD &= 0xF0;		//???????
	TMOD |= 0x01;		//???????
	TL0 = 0x18;		//??????
	TH0 = 0xFC;		//??????
	TF0 = 0;		//??TF0??
	ET0 = 1;
	EA = 1;
	TR0 = 1;		//???0????
}


void timer0()interrupt 1
{
	TR0 = 0;
	if(time1_enable)
	{	
		time1_cnt--;
		time2_cnt--;
		if(!time1_cnt)
			time1_flag = 1;
		if(!time2_cnt)
			time2_flag = 1;
	}
	TL0 = 0x18;		//??????
	TH0 = 0xFC;		//??????
	TR0 = 1;
}