#include "reg52.h"

sfr AUXR = 0x8e;

sbit L1 =P0^0;
sbit L2 =P0^1;
sbit L3 =P0^2;
sbit L4 =P0^3;
sbit L5 =P0^4;
sbit L6 =P0^5;
sbit L7 =P0^6;
sbit L8 =P0^7;

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
		case 0:
			P2 = (P2 & 0x1f) | 0x00;
		break;
	}
}

void InitSystem()
{
	SelectHC573(5);
	P0 = 0x00;
	SelectHC573(4);
	P0 = 0xff;
}


void InitUart()
{
	TMOD = 0x20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	TR1 = 1;
	
	SCON = 0x50;
	AUXR = 0x00;
	
	ES = 1;
	EA = 1;
}


unsigned char command =0x00;
void ServiceUart() interrupt 4
{
	if(RI == 1)
	{
		command = SBUF;
		RI = 0;
	}

}


void SendByte(unsigned char dat)
{
	SBUF = dat;
	while(TI == 0);
	TI = 0;
}

void SendString(unsigned char *str)
{
	while(*str != '\0')
	{
		SendByte(*str++);
	}
}

void Working()
{
	if(command != 0)
	{
		switch(command )
		{
			case 0xa1:
				L1 = 0;
				command = 0x00;
			break;
			case 0xb1:
				L1 = 1;
				command = 0x00;
			break;
			
			case 0xa2:
				L2 = 0;
				command = 0x00;
			break;
			case 0xb2:
				L2 = 1;
				command = 0x00;
			break;
			
			case 0xa3:
				L3 = 0;
				command = 0x00;
			break;
			case 0xb3:
				L3= 1;
				command = 0x00;
			break;
			
			case 0xa4:
				L4 = 0;
				command = 0x00;
			break;
			case 0xb4:
				L4= 1;
				command = 0x00;
			break;
			
			case 0xa5:
				L5 = 0;
				command = 0x00;
			break;
			case 0xb5:
				L5= 1;
				command = 0x00;
			break;
			
			case 0xa6:
				L6 = 0;
				command = 0x00;
			break;
			case 0xb6:
				L6= 1;
				command = 0x00;
			break;
			
			case 0xa7:
				L7 = 0;
				command = 0x00;
			break;
			case 0xb7:
				L7= 1;
				command = 0x00;
			break;
			
			case 0xa8:
				L8 = 0;
				command = 0x00;
			break;
			case 0xb8:
				L8= 1;
				command = 0x00;
			break;
		}
	
	}
	
}




void main()
{	
	
	InitUart();
	InitSystem();
	SendString("hallo word!\r\n");
	while(1)
	{
		Working();
	}
	
}