#include <reg51.h>                 


sbit L1 = P0^0;                                      
sbit L2 = P0^1;
sbit L3 = P0^2;                                      
sbit L4 = P0^3; 

void delay(unsigned char x)          
{
	unsigned char i,j;
	for(i = 0;i < x;i++)
	for(j = 0;j < 200;j++);
}

void main(void)                     
{
	P0 = 0x00;					  	
	while(1)                       
	{
		L1 = !L1;	
		L2 = !L2;	
		L3 = !L3;	
		L4 = !L4;
		delay(250);                 
	}
}
