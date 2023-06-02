#include <reg51.h> 
#include "time.h"
#include "led.h"

sbit LED1 = P0^0;
sbit LED2 = P0^1;
 




void main(void)                     
{	
	led_init();
	Timer0Init();
	
	while(1)
	{
		led1_task();
		led2_task();
	}
}
