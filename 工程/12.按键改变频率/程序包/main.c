#include "reg52.h"


sbit S1 = P3^0;
sbit S2 = P3^1;
sbit S3 = P3^2;
sbit S4 = P3^3;

sbit P2_0 = P2^0;
sbit P2_1 = P2^1;


sbit P1_0 = P1^0;
sbit P1_1 = P1^1;
sbit P1_2 = P1^2;
sbit P1_3 = P1^3;

unsigned int t1 = 10;//50Hz
unsigned int t2 = 20;//25Hz
char a[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
char seg[12] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8c,0xc1};

char Flag_1 = 1; 
char Flag_2 = 1;
char Flag_3 = 1; 
char Flag_4 = 1;
void Key_scan()
{
	if(S1 == 0)
	{
		Flag_1 = 0;
	}
	else if(!Flag_1)
	{
		Flag_1 = 1;
		t1-=1;
	}
	
	if(S2 == 0)
	{
		Flag_2 = 0;
	}
	else if(!Flag_2)
	{
		Flag_2 = 1;
		t1+=1;
	}
	
//	if(S3 == 0)
//	{
//		Flag_3 = 0;
//	}
//	else if(!Flag_3)
//	{
//		Flag_3 = 1;
//		t2-=5;
//	}
//	
//	if(S4 == 0)
//	{
//		Flag_4 = 0;
//	}
//	else if(!Flag_4)
//	{
//		Flag_4 = 1;
//		t2+=5;
//	}

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



void SMG_Dynamic(unsigned int i)
{
	SMG_bit(1,i/1000);
	delay_ms(10);
	SMG_bit(2,i/100%10);
	delay_ms(10);
	SMG_bit(3,i/10%10);
	delay_ms(10);
	SMG_bit(4,i%10);
	delay_ms(10);
	SMG_bit(5,0x00);
	delay_ms(10);
}





void InitTimer0()
{
	TMOD = 0x11;
	TH0 = (65535 - 1000) / 256; // 50ms
	TL0 = (65535 - 1000) % 256;
	TR0 = 1;
	
	ET0 = 1;
	EA = 1;
	
}

int count1 = 0;
int count2 = 0;
void ServiceTimer0() interrupt 1
{
	TH0 = (65535 - 1000) / 256;//1ms
	TL0 = (65535 - 1000) % 256;
	
	count1++;
	if(count1 == t1)//t1 ms
	{
		count1 = 0;
		P2_0 = ~P2_0;
	}
	
	count2++;
	if(count2 == t2)//t2 ms
	{
		count2 = 0;
		P2_1 = ~P2_1;
	}
}



void INT0_Init(void)
{
	IT0 = 1; //外部中断触发模式，下降沿
	EA =1; //外部中断0开关
	EX0 =1; //外部中断总开关
	
}


void exint0() interrupt 0       //INT0
{
	t2-=5;
}


void INT1_Init(void)
{
	IT1 =1;//外部中断触发模式，下降沿
	EA =1;//外部中断1开关
	EX1 =1;//外部中断总开关
	
}

void exint1() interrupt 2       //INT1
{
	t2+=5;
}



int f1;
int f2;
int num;
void main()
{
	INT0_Init();
	INT1_Init();
	InitTimer0();
	while(1)
	{
		if(f1>99)
		{
			t1=10;
		}
		if(f2>99)
		{
			t2 = 20;
		}
		f1 = 500/t1;
		f2 = 500/t2;
		num = f1*100+f2;
		Key_scan();
		SMG_Dynamic(num);
	}
}
