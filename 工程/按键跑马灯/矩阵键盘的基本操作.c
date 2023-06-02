#include "reg52.h"



sbit C1 = P2^0;
sbit C2 = P2^1;
sbit C3 = P2^2;
sbit C4 = P2^3;

sbit R1 = P2^4;
sbit R2 = P2^5;
sbit R3 = P2^6;
sbit R4 = P2^7;

unsigned int i = 0;
char a[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};

char Flag = 0; 	
void ScanKeysMulti()
{
	C1 = 0;
	C2 = C3 = C4 = 1;
	R1 = R2 = R3 = R4 =1;
	if(R1 == 0)
	{
		Flag = 1;
	}
	if(Flag == 1 && R1 == 1)
	{
		Flag = 0;
		i += 1;
		if(i == 8)
			i = 0;
	}
}

void main()
{
	while(1)
	{
		P0 = a[i];
		ScanKeysMulti();
	}
}