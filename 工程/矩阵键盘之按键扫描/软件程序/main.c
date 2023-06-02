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

unsigned char KeyNum = 0;
unsigned char Key_Scan()
{
	
	//?????
	KEYIN1 = 1;	KEYIN2 = 1;	KEYIN3 = 1;	KEYIN4 = 1;
	KEYOUT1 = 0;KEYOUT2 = 1;KEYOUT3 = 1;KEYOUT4 = 1;
		
	if(!KEYIN1||!KEYIN2||!KEYIN3||!KEYIN4) 			
	{
		DelayXms(10);		
		if(!KEYIN1||!KEYIN2||!KEYIN3||!KEYIN4) 			
		{
			if(!KEYIN1)
				KeyNum = 1;
			if(!KEYIN2)
				KeyNum = 2;
			if(!KEYIN3)
				KeyNum = 3;
			if(!KEYIN4)
				KeyNum = 4;
		}while(!KEYIN1||!KEYIN2||!KEYIN3||!KEYIN4);	
	}
	
	//?????
	KEYIN1 = 1;	KEYIN2 = 1;	KEYIN3 = 1;	KEYIN4 = 1;
	KEYOUT1 = 1;KEYOUT2 = 0;KEYOUT3 = 1;KEYOUT4 = 1;
		
	if(!KEYIN1||!KEYIN2||!KEYIN3||!KEYIN4) 			
	{
		DelayXms(10);		
		if(!KEYIN1||!KEYIN2||!KEYIN3||!KEYIN4) 			
		{
			if(!KEYIN1)
				KeyNum = 5;
			if(!KEYIN2)
				KeyNum = 6;
			if(!KEYIN3)
				KeyNum = 7;
			if(!KEYIN4)
				KeyNum = 8;
		}while(!KEYIN1||!KEYIN2||!KEYIN3||!KEYIN4);	
	}
	
	//?????
	KEYIN1 = 1;	KEYIN2 = 1;	KEYIN3 = 1;	KEYIN4 = 1;
	KEYOUT1 = 1;KEYOUT2 = 1;KEYOUT3 = 0;KEYOUT4 = 1;
		
	if(!KEYIN1||!KEYIN2||!KEYIN3||!KEYIN4) 			
	{
		DelayXms(10);		
		if(!KEYIN1||!KEYIN2||!KEYIN3||!KEYIN4) 			
		{
			if(!KEYIN1)
				KeyNum = 9;
			if(!KEYIN2)
				KeyNum = 10;
			if(!KEYIN3)
				KeyNum = 11;
			if(!KEYIN4)
				KeyNum = 12;
		}while(!KEYIN1||!KEYIN2||!KEYIN3||!KEYIN4);	
	}
	
	//?????
	KEYIN1 = 1;	KEYIN2 = 1;	KEYIN3 = 1;	KEYIN4 = 1;
	KEYOUT1 = 1;KEYOUT2 = 1;KEYOUT3 = 1;KEYOUT4 = 0;
		
	if(!KEYIN1||!KEYIN2||!KEYIN3||!KEYIN4) 			
	{
		DelayXms(10);		
		if(!KEYIN1||!KEYIN2||!KEYIN3||!KEYIN4) 			
		{
			if(!KEYIN1)
				KeyNum = 13;
			if(!KEYIN2)
				KeyNum = 14;
			if(!KEYIN3)
				KeyNum = 15;
			if(!KEYIN4)
				KeyNum = 16;
		}while(!KEYIN1||!KEYIN2||!KEYIN3||!KEYIN4);	
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