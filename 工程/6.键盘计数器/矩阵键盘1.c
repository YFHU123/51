#include "reg52.h"

sbit HC138_A = P2^5;
sbit HC138_B = P2^6;
sbit HC138_C = P2^7;

sfr P4 = 0xC0;

sbit R1 = P3^0;
sbit R2 = P3^1;
sbit R3 = P3^2;
sbit R4 = P3^3;

sbit C4 = P3^4;
sbit C3 = P3^5;
sbit C2 = P4^2;
sbit C1 = P4^4;


unsigned char code SMG_duanma[10]=
	{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};


void SelectHC573(unsigned char channel)
{
	switch(channel)
	{
		case 4:
			P2 = (P2 & 0x1f) | 0x80;
		break;
		
		case 5:
			P2 = (P2 & 0x1f) | 0xa0;
		break;
		
		case 6:
			P2 = (P2 & 0x1f) | 0xc0;
		break;
		
		case 7:
			P2 = (P2 & 0x1f) | 0xe0;
		break;
	}
}

void DisplaySMG_Bit(unsigned char value,unsigned char pos)
{
	P0 = 0xff;
	SelectHC573(6);
	P0 = 0x01 << pos;
	SelectHC573(7);
	P0 = value;
}

void DelaySMG(unsigned int t)
{
	while(t--);
}


int value = 0;

void Display_Dynamic()
{
	
	DisplaySMG_Bit(SMG_duanma[value%10],7);
	DelaySMG(500);
	DisplaySMG_Bit(SMG_duanma[(value/10)%10],6);
	DelaySMG(500);
	DisplaySMG_Bit(SMG_duanma[(value/100)%10],5);
	DelaySMG(500);
	DisplaySMG_Bit(SMG_duanma[(value/1000)%10],4);
	DelaySMG(500);

}

void ScanKeyMulti()
{
	R1 = 0;
	R2 = R3 = R4 =1;
	C1 = C2 = C3 = C4 =1;
	if(C1 == 0)
	{
		while(C1 == 0);
		value+=1;
	}

	if(C2 == 0)
	{
		while(C2 == 0);
		value-=1;
	}
}

void main()
{
	SelectHC573(4);
	P0 = 0x00;
	
	while(1)
	{
		Display_Dynamic();
		ScanKeyMulti();
	}

}