#include <reg51.h>                 


sbit LED1 = P0^0;                                      
sbit LED2 = P0^1;
sbit LED3 = P0^2;                                      
sbit LED4 = P0^3; 


sbit C1 = P2^0;
sbit C2 = P2^1;
sbit C3 = P2^2;
sbit C4 = P2^3;



void main(void)                     
{
	unsigned char led1_flag = 0;
	unsigned char led2_flag = 0;
	unsigned char led3_flag = 0;
	unsigned char led4_flag = 0;
	while(1)                       
	{
		if(!C1)
		{
			led1_flag = 1;
			
		}
		if(led1_flag == 1 && C1 == 1)
		{
			led1_flag = 0;
			LED1 = ~LED1;
		}
		
		if(!C2)
		{
			led2_flag = 1;
			
		}
		if(led2_flag == 1 && C2 == 1)
		{
			led2_flag = 0;
			LED2 = ~LED2;
		}
		
		if(!C3)
		{
			led3_flag = 1;
			
		}
		if(led3_flag == 1 && C3 == 1)
		{
			led3_flag = 0;
			LED3 = ~LED3;
		}
		
		if(!C4)
		{
			led4_flag = 1;
			
		}
		if(led4_flag == 1 && C4 == 1)
		{
			led4_flag = 0;
			LED4 = ~LED4;
		}
	}
}
