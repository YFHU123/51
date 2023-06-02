#include "reg52.h"

char a[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};


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
	for(i=0;i<8;i++)
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