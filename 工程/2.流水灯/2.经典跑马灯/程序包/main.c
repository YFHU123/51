#include "reg52.h"

char a[9] = {0xff,0xfe,0xfc,0xf8,0xf0,0xe0,0xc0,0x80,0x00};


void delay_ms(int ms)
{
    int i = 0;
    int j = 0;
    for(i=0;i<ms;i++)
    {
        for(j=0;j<100;j++){}
    }
}


void run()
{
	int i;
	for(i=0;i<9;i++)
	{
		P2 = a[i];
		delay_ms(200);
	}
	for(i=8;i>=0;i--)
	{
		P2 = a[i];
		delay_ms(200);
	}
}



void main()
{

	while(1)
	{
		run();
	}
}