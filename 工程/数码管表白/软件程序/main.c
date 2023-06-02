#include "reg51.h"

sbit P0_0 = P0^0;
sbit P0_1 = P0^1;

sbit KEY1 = P0^0;
sbit KEY2 = P0^1;

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

char bu1Flag = 0;

int numA = 0;
int numB = 0;

int status = 0;

char seg[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

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

//char key1Flag = 0; 
//char key2Flag = 0;
//main()
//{
//    int i = 0;
//    while(1)
//    {  
//        if(KEY1 == 0)
//        {
//            key1Flag = 1;
//        }
//        if(key1Flag == 1 && KEY1 == 1)
//        {
//            key1Flag = 0;
//            i = i+1;
//        }
//        
//        if(KEY2 == 0)
//        {
//            key2Flag = 1;
//        }
//        if(key2Flag == 1 && KEY2 == 1)
//        {
//            key2Flag = 0;
//            i = i+2;
//        }
//       
//        
//        if(i>9)
//        {
//            i = 9;
//        }
//        P1 = seg[i];
//       
//    }   
//}

void SMG_pos(unsigned char i)
{
	switch(i)
	{
		case 1:
			P2_4 = 1;
			P2_5 = 0;
			P2_6 = 0;
			P2_7 = 0;
		break;
		
		case 2:
			P2_4 = 0;
			P2_5 = 1;
			P2_6 = 0;
			P2_7 = 0;
		break;
		
		case 3:
			P2_4 = 0;
			P2_5 = 0;
			P2_6 = 1;
			P2_7 = 0;
		break;
		
		case 4:
			P2_4 = 0;
			P2_5 = 0;
			P2_6 = 0;
			P2_7 = 1;
		break;
		
		case 5:
			P2_4 = 0;
			P2_5 = 0;
			P2_6 = 0;
			P2_7 = 0;
		break;
	}
}

void SMG_bit(unsigned char pos,value)
{
	SMG_pos(pos);
	P1 = value;
}

void SMG_Dynamic_1314()
{
	SMG_bit(1,seg[1]);
	delay_ms(10);
	SMG_bit(2,seg[3]);
	delay_ms(10);
	SMG_bit(3,seg[1]);
	delay_ms(10);
	SMG_bit(4,seg[4]);
	delay_ms(10);
	SMG_bit(5,0x00);
	delay_ms(10);
}

void SMG_Dynamic_LOVE()
{
	SMG_bit(1,0xc7);//"L" 1100 0111 0xc7
	delay_ms(10);
	SMG_bit(2,0xc0);//"O" 1100 0000 0xc0
	delay_ms(10);
	SMG_bit(3,0xc1);//"V" 1100 1000 0xc1
	delay_ms(10);
	SMG_bit(4,0x86);//"E" 1000 0110 0x86
	delay_ms(10);
	SMG_bit(5,0x00);
	delay_ms(10);
}

main()
{
	int flag = 0;
	int time = 0;
    while(1)
    {
			time++;
			if(time>25)
			{
				time = 0;
				flag = !flag;
			}
			if(flag == 0)
			{
				SMG_Dynamic_LOVE();
			}
			else
			{
				SMG_Dynamic_1314();
			}
		
		
			
    }   
}