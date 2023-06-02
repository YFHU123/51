#include "reg51.h"

sbit P2_0 = P2 ^ 0;
sbit P2_1 = P2 ^ 1;
sbit S1 = P3^0;
sbit S2 = P3^1;

unsigned int num1 = 0;
unsigned int num2 = 0;

void delay_ms(int ms)
{
    int i = 0;
    int j = 0;
    for(i=0;i<ms;i++)
    {
        for(j=0;j<100;j++){}
    }
}


void KEY()
{
	if(S1==0)
	{
		delay_ms(100);
		if(S1==0)
		{
		num1++;
		}
	}
	if(S2==0)
	{
		delay_ms(100);
		if(S2==0)
		{
		num2++;
		}
	}
	if(num1>num2)
	{
		P2_0 = 0;
		P2_1 = 1;
	}
	else if(num1<num2)
	{
		P2_1 = 0;
		P2_0 = 1;
	}
	else
	{
		P2_1 = 1;
		P2_0 = 1;
	}
}

main()
{
    while(1)
    {
       KEY();
    }   
}