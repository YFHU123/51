#include "reg52.h"

sbit S1 = P3^2;

sbit L1 = P2^0;
sbit L2 = P2^1;
sbit L3 = P2^2;
sbit L4 = P2^3;
sbit L5 = P2^4;
sbit L6 = P2^5;
sbit L7 = P2^6;
sbit L8 = P2^7;

sbit P1_0 = P1^0;
sbit P1_1 = P1^1;
sbit P1_2 = P1^2;
sbit P1_3 = P1^3;

unsigned int key_cnt = 0;
char a[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
char seg[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

char Flag = 0; 	
void Key_scan()
{

	if(S1 == 0)
	{
		Flag = 1;
	}
	if(Flag == 1 && S1 == 1)
	{
		Flag = 0;
		key_cnt += 1;
	}
}

void delay_ms(int ms)
{
    int i = 0;
    int j = 0;
    for(i=0;i<ms;i++)
    {
        for(j=0;j<100;j++){}
    }
}




void SMG_pos(unsigned char i)
{
	switch(i)
	{
		case 1:
			P1_0 = 1;
			P1_1 = 0;
			P1_2 = 0;
			P1_3 = 0;
		break;
		
		case 2:
			P1_0 = 0;
			P1_1 = 1;
			P1_2 = 0;
			P1_3 = 0;
		break;
		
		case 3:
			P1_0 = 0;
			P1_1 = 0;
			P1_2 = 1;
			P1_3 = 0;
		break;
		
		case 4:
			P1_0 = 0;
			P1_1 = 0;
			P1_2 = 0;
			P1_3 = 1;
		break;
		
		case 5:
			P1_0 = 0;
			P1_1 = 0;
			P1_2 = 0;
			P1_3 = 0;
		break;
	}
}

void SMG_bit(unsigned char pos,value)
{
	SMG_pos(pos);
	P0 = seg[value];
}



void SMG_Dynamic()
{
	SMG_bit(1,key_cnt/1000);
	delay_ms(10);
	SMG_bit(2,key_cnt/100%10);
	delay_ms(10);
	SMG_bit(3,key_cnt/10%10);
	delay_ms(10);
	SMG_bit(4,key_cnt%10);
	delay_ms(10);
	SMG_bit(5,0x00);
	delay_ms(10);
}










void main()
{
	while(1)
	{
		P2 = a[key_cnt%8];
		Key_scan();
		SMG_Dynamic();
	}
}