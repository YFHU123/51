#include <reg51.h>                 


sbit LED1 = P0^0;
sbit LED2 = P0^1;  


#define LED1_DELAY_TIME 10000
#define LED2_DELAY_TIME 20000


void main(void)                     
{
	unsigned int led1_cnt;
	unsigned char led1_flag;
	unsigned int led2_cnt;
	unsigned char led2_flag;
	led1_cnt = LED1_DELAY_TIME;
	led2_cnt = LED2_DELAY_TIME;
	while(1)                       
	{
		if(led1_cnt)
			led1_cnt--;
		if(!led1_cnt)
		{
			led1_flag = 1;
		}
		if(led1_flag == 1)
		{
			led1_flag = 0;
			LED1 = ~LED1;
			led1_cnt = LED1_DELAY_TIME;
		}
		
		if(led2_cnt)
			led2_cnt--;
		if(!led2_cnt)
		{
			led2_flag = 1;
		}
		if(led2_flag == 1)
		{
			led2_flag = 0;
			LED2 = ~LED2;
			led2_cnt = LED2_DELAY_TIME;
		}
	}
}
