#include "reg51.h"



sbit KEYIN1 = P2^0;
sbit KEYIN2 = P2^1;
sbit KEYIN3 = P2^2;
sbit KEYIN4 = P2^3;

sbit KEYOUT1 = P2^4;
sbit KEYOUT2 = P2^5;
sbit KEYOUT3 = P2^6;
sbit KEYOUT4 = P2^7;

sbit P3_0 = P3^0;
sbit P3_1 = P3^1;
sbit P3_2 = P3^2;
sbit P3_3 = P3^3;




char seg[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

void DelayXms(int ms)
{
    int i = 0;
    int j = 0;
    for(i=0;i<ms;i++)
    {
        for(j=0;j<100;j++){}
    }
}

unsigned char Key_Scan()
{
	
	unsigned char temp,temp2;
	static unsigned char KeyNum = 0;
	
	P2 = 0xf0;							//4????,4????,??“0”,???“1”
	temp = P2;							//?P2 IO?
	
	if(temp != 0xf0)						//????????
	{
		DelayXms(10);
		if(temp != 0xf0)					//??????????(??)
		{
			temp = P2 & 0xf0;			//????????
			P2 = 0x0f;					//4????,4????,??“0”,???“1”
			temp2 = P2 & 0x0f;			//???????????		
		}
	}
	
	switch(temp + temp2)//???
	{
		case 0xee : KeyNum = 1;break;
		case 0xed : KeyNum = 2;break;
		case 0xeb : KeyNum = 3;break;
		case 0xe7 : KeyNum = 4;break;
		
		case 0xde : KeyNum = 5;break;		
		case 0xdd : KeyNum = 6;break;
		case 0xdb : KeyNum = 7;break;
		case 0xd7 : KeyNum = 8;break;
		
		case 0xbe : KeyNum = 9;break;		
		case 0xbd : KeyNum = 0;break;
		case 0xbb : KeyNum = 10;break;
		case 0xb7 : KeyNum = 11;break;

		case 0x7e : KeyNum = 12;break;		
		case 0x7d : KeyNum = 13;break;
		case 0x7b : KeyNum = 14;break;
		case 0x77 : KeyNum = 15;break;		
	}
	
	return KeyNum;	
}



void SMG_pos(unsigned char i)
{
	switch(i)
	{
		case 1:
			P3_0 = 1;
			P3_1 = 0;
			P3_2 = 0;
			P3_3 = 0;
		break;
		
		case 2:
			P3_0 = 0;
			P3_1 = 1;
			P3_2 = 0;
			P3_3 = 0;
		break;
		
		case 3:
			P3_0 = 0;
			P3_1 = 0;
			P3_2 = 1;
			P3_3 = 0;
		break;
		
		case 4:
			P3_0 = 0;
			P3_1 = 0;
			P3_2 = 0;
			P3_3 = 1;
		break;
		
		case 5:
			P3_0 = 0;
			P3_1 = 0;
			P3_2 = 0;
			P3_3 = 0;
		break;
	}
}

void SMG_bit(unsigned char pos,value)
{
	SMG_pos(pos);
	P0 = seg[value];
}



void SMG_Dynamic(unsigned char i)
{
	SMG_bit(1,(i/1000)%10);
	DelayXms(10);
	SMG_bit(2,(i/100)%10);
	DelayXms(10);
	SMG_bit(3,(i/10)%10);
	DelayXms(10);
	SMG_bit(4,i%10);
	DelayXms(10);
	SMG_bit(5,0x00);
	DelayXms(10);
}



void main()
{
	char key1Flag = 0; 
	int i = 0;
    while(1)
    {  
        SMG_Dynamic(Key_Scan());
    }   
}