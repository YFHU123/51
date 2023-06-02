#include "led.h"
#include "time.h"

void led_init()
{
	time1_cnt = LED1_SHINE_TIME;
	time1_flag = 0;
	
	time2_cnt = LED2_SHINE_TIME;
	time2_flag = 0;
	P07 = 0;
}

void led1_task()
{
	static unsigned char step = 0;
	switch(step)
	{
		case 0:
			if(_testbit_(time1_flag))
			{
				//time1_flag = 0;
				time1_cnt = LED1_SHINE_TIME;
				P00 = 1;
				P01 = 1;
				P02 = 1;
				P03 = 0;
				step = 1;//×´Ì¬ÇÐ»»
			}
			break;
		case 1:
			if(_testbit_(time1_flag))
			{
				//time1_flag = 0;
				time1_cnt = LED1_SHINE_TIME;
				P00 = 1;
				P01 = 1;
				P02 = 0;
				P03 = 1;
				step = 2;//×´Ì¬ÇÐ»»
			}
			break;
		case 2:
			if(_testbit_(time1_flag))
			{
				//time1_flag = 0;
				time1_cnt = LED1_SHINE_TIME;
				P00 = 1;
				P01 = 0;
				P02 = 1;
				P03 = 1;
				step = 3;//×´Ì¬ÇÐ»»
			}
			break;
		case 3:
			if(_testbit_(time1_flag))
			{
				//time1_flag = 0;
				time1_cnt = LED1_SHINE_TIME;
				P00 = 0;
				P01 = 1;
				P02 = 1;
				P03 = 1;
				step = 0;//×´Ì¬ÇÐ»»
			}
			break;
			default:break;
	}
		
}

void led2_task()
{
	static unsigned char step = 0;
	switch(step)
	{
		case 0:
			if(_testbit_(time2_flag))
			{
				//time2_flag = 0;
				time2_cnt = LED2_SHINE_TIME;
				P04 = 1;
				P05 = 1;
				P06 = 1;
				P07 = 0;
				step = 1;//×´Ì¬ÇÐ»»
			}
			break;
		case 1:
			if(_testbit_(time2_flag))
			{
				//time2_flag = 0;
				time2_cnt = LED2_SHINE_TIME;
				P04 = 1;
				P05 = 1;
				P06 = 0;
				P07 = 1;
				step = 2;//×´Ì¬ÇÐ»»
			}
			break;
		case 2:
			if(_testbit_(time2_flag))
			{
				//time2_flag = 0;
				time2_cnt = LED2_SHINE_TIME;
				P04 = 1;
				P05 = 0;
				P06 = 1;
				P07 = 1;
				step = 3;//×´Ì¬ÇÐ»»
			}
			break;
		case 3:
			if(_testbit_(time2_flag))
			{
				//time1_flag = 0;
				time2_cnt = LED2_SHINE_TIME;
				P04 = 0;
				P05 = 1;
				P06 = 1;
				P07 = 1;
				step = 0;//×´Ì¬ÇÐ»»
			}
			break;
			default:break;
	}
}