#include "reg52.h"

sbit S1 = P3^0;
unsigned int i = 0;

void Delay(unsigned int t)
{
	while(t--);
}

char a[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};

void Key()
{
	if(S1 == 0)
	{
		Delay(10000);
		while(S1==0);
		i+=1;
		if(i==8)
			i=0;
	}
}

//void Run()
//{
//	for(i=0;i<4;i++)
//	{
//		P0 = a[i];
//		Delay(100000);
//	}
//}

void main()
{
	while(1)
	{
		Key();
		P0 = a[i];
	}
}
