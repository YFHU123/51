#include <reg51.h> 
#include "time.h"


sbit LED1 = P0^0;

 
#define LED1_SHINE_TIME 1000;




void main(void)                     
{	
	time1_cnt = LED1_SHINE_TIME;
	time1_enable = 1;
	time1_flag = 0;
	
  Timer0Init();
	
	while(1)
	{
		if(time1_flag)
		{
			time1_flag = 0;
			LED1 = ~LED1;
			time1_cnt = LED1_SHINE_TIME;
		}
		
	}
}
