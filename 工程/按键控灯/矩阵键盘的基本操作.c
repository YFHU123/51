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
char a[9] = {0xff,0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};




char Flag = 0; 	
unsigned char key_num = 0;
void ScanKeysMulti()
{
	R1 = 0;
	R2 = R3 = R4 = 1;
	C1 = C2 = C3 = C4 =1;
	if(C1 == 0)
	{
		while(C1 == 0);
		key_num = 1;
		P0 = a[key_num];
	}
	else if(C2 == 0)
	{
		while(C2 == 0);
		key_num = 2;
		P0 = a[key_num];
	}
	else if(C3 == 0)
	{
		while(C3 == 0);
		key_num = 3;
		P0 = a[key_num];
	}
	else if(C4 == 0)
	{
		while(C4 == 0);
		key_num = 4;
		P0 = a[key_num];
	}
	
}

void main()
{
	while(1)
	{
		
		ScanKeysMulti();
	}
}