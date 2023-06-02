#include <reg52.h>
 
/****配置LED****/
sbit LED = P0^0;
bit Direct_flag = 0; 	//LED????????
/****函数声明****/
void T0init();
/****全局变量****/
unsigned int PWM_wanttime=0;			//??????????????
unsigned int Breath_wanttime=0;		//??????????????????
unsigned int  PWM_value = 0;				//??????
 
void main()
{
	T0init();
	while(1)
	{
	}	
}



void T0init()
{
    TMOD |= 0x01;	
    TH0=0XFC;   
    TL0=0X66;
    ET0 = 1;    
    TR0 = 1;    
    EA = 1;     
}
 
void Time0(void) interrupt 1
{
 
    TH0=0XFC;   
    TL0=0X66;
 
    PWM_wanttime++;			//改变占空比一次的标志
    Breath_wanttime++;		//呼气和吸气改变一次的标志
 
 
    if(PWM_wanttime == PWM_value)  //判断是否到了点亮LED灯的情况    	
        LED = 0;                    	
    if(PWM_wanttime == 10)            	
    {
        LED = 1;                    	
        PWM_wanttime = 0;              	
    }
 
 
    if((Breath_wanttime == 200) && (Direct_flag == 0))	  //200ms 改变一次占空比,每次改变10%
    {                               
        Breath_wanttime = 0;
        PWM_value++;				
 
        if(PWM_value == 9)          
            Direct_flag = 1; 
    }
 
    if((Breath_wanttime == 200) && (Direct_flag == 1))	
    {                               
        Breath_wanttime = 0;
        PWM_value--;				
 
        if(PWM_value == 1)          
            Direct_flag = 0; 
    }
}
 