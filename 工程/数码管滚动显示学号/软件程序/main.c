#include "reg51.h"

sbit P2_0 = P2^0;
sbit P2_1 = P2^1;
sbit P2_2 = P2^2;
sbit P2_3 = P2^3;

sbit P2_4 = P2^4;
sbit P2_5 = P2^5;
sbit P2_6 = P2^6;
sbit P2_7 = P2^7;

sbit LED_A = P2^0;
sbit LED_B = P2^0;

sbit P1_0 = P1 ^ 0;

sbit S1 = P3^0;
sbit S2 = P3^1;

char bu1Flag = 0;

int numA = 0;
int numB = 0;

int status = 0;



char SMG_duanma[16] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};

void delay_ms(int ms)
{
    int i = 0;
    int j = 0;
    for(i=0;i<ms;i++)
    {
        for(j=0;j<100;j++){}
    }
}

//跑马灯  2023年4月18日 11点39分
void fun_pmd()
{
    //步骤1: 只亮0号灯       
    P2 = 0xFE; //1111,1110   
    delay_ms(200);      
    
    //步骤2 只亮1号灯 
    P2 = 0xFD;   //1111,1101        
    delay_ms(200);

    //步骤3 只亮2号灯
    P2 = 0xFB;   //1111,1011    
    delay_ms(200);

    //步骤4 只亮3号灯
    P2 = 0xF7;   //1111,0111      
    delay_ms(200);
}

char led[4]={0xFE,0xFD,0xFB,0xF7};
//跑马灯  2023年4月18日 11点39分
void fun_pmd2()
{
    int i = 0;
    for(i=0;i<4;i++)
    {   
        P2 = led[i];   //1111,0111      
        delay_ms(200);
    }
}

void fun_lsd()
{
    
}



//void SMG()
//{
//	int i ;
//	for (i = 0;i<10;i++)
//	{
//		P1 = SMG_duanma[i];
//		delay_ms(500);
//	}

//}


//unsigned char i = 0;
//	
//unsigned flag1 = 0;
//unsigned flag2 = 0;
//void KEY()
//{
//	if(S1 == 0)
//	{
//		flag1 = 1;
//	}
//	if(flag1 == 1 && S1 == 1)
//	{
//		flag1 = 0;
//		i+=2;
//	}
//	
//	
//	if(S2 == 0)
//	{
//		flag2 = 1;
//	}
//	if(flag2 == 1 && S2 == 1)
//	{
//		flag2 = 0;
//		i+=1;
//	}

//	if(i > 9)
//	{
//		i = 0;
//	}
//	
//}






main()
{
    while(1)
    { 
			
			P2_4 = 1;
			P2_5 = 0;
			P2_6 = 0;
			P2_7 = 0;
			P1 = 0x80;
			delay_ms(500);
			
			P2_4 = 0;
			P2_5 = 1;
			P2_6 = 0;
			P2_7 = 0;
			P1 = 0x80;
			delay_ms(500);
			
			P2_4 = 0;
			P2_5 = 0;
			P2_6 = 1;
			P2_7 = 0;
			P1 = 0x80;
			delay_ms(500);			
			
		  P2_4 = 0;
			P2_5 = 0;
			P2_6 = 0;
			P2_7 = 1;
			P1 = 0x80;
			delay_ms(500);
			
    }   
}