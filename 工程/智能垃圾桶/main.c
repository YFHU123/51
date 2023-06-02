#include "reg52.h"
#include "intrins.h"
 

sbit Trig     = P1^5;
sbit Echo     = P1^6;
sbit sg90_con = P1^1;

 
char angle;
char angle_bak;
char cnt = 0;

 
void Delay150ms()		//@11.0592MHz
{
	unsigned char i, j, k;
 
	_nop_();
	i = 2;
	j = 13;
	k = 237;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
 
void Delay2000ms()		//@11.0592MHz
{
	unsigned char i, j, k;
 
	_nop_();
	i = 15;
	j = 2;
	k = 235;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
 
void Delay10us()		//@11.0592MHz
{
	unsigned char i;
 
	i = 2;
	while (--i);
}
 
void Timer0Init(void)		//500微秒@11.0592MHz
{
	//AUXR &= 0x7F;		
	TMOD &= 0xF0;	//设置定时器模式16位
	TMOD |= 0x01;	//设置定时器模式
	TL0 = 0x33;		//设置定时器初始值0.5ms
	TH0 = 0xFE;		//设置定时器初始
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;		//打开定时器0中断
	EA  = 1;		//打开总中断EA
}
 
void Timer1Init()		
{	
	TMOD &= 0x0F;		
	TMOD |= 0x10;
	TH1 = 0;
	TL1 = 0;
}
 
void startHC()
{
	Trig = 0;
	Trig = 1;
	Delay10us();
	Trig = 0;
}
 
double get_distance()
{
		double time;
		//定时器清零，以便下一次测距
		TH1 = 0;
		TL1 = 0;
	//1.让它发送波:给Trig端口至少10us的高电平
		startHC();
		//2. 开始发送波:Echo由低电平跳转到高电平
		while(Echo == 0);
		//   开始发送波，启动定时器
		TR1 = 1;
		//3. 接收返回波:Echo由低电平转回高电平
		while(Echo == 1);
		//   接收返回波，停止定时器
		TR1 = 0;
		//4. 计算时间
		time = (TH1 * 256 + TL1)*1.085;//us???
		//5. 距离 = 速度 (340m/s)* 时间/2
		return  (time * 0.017);
}
 

 
void initSG90_0()
{
	angle = 1;      //初始角度0度，0.5ms，溢出1就是高电平
	cnt = 0;
	sg90_con = 1;//一开始从高电平开始
}
 
void openDustbin()
{
	char n;
	angle = 3; //90度，1.5ms高电平
	//舵机开盖
	if(angle_bak != angle){
		cnt = 0;
		for(n = 0; n < 2; n++)
			Delay150ms();
		Delay2000ms();
	}
	angle_bak = angle;
}
 
void closeDustbin()
{
	//关盖
	angle = 1; //0度
	angle_bak = angle;
	cnt = 0;
	Delay150ms();
}

 
void main()
{
	double dis;
	
	Timer0Init();
	Timer1Init();
	
	initSG90_0();//舵机的初始位置
	
	while(1){
		
		dis = get_distance();//超声波测距
		if(dis < 10 ){
			//开盖
			openDustbin();
		}else{
			//关盖
			closeDustbin();
		}
	}
}
 
void Time0Handler() interrupt 1
{
	cnt++;  					//统计溢出的次数
	//重新给初值
	TL0 = 0x33;
	TH0 = 0xFE;
	
	//PWM控制
	if(cnt < angle){
		sg90_con = 1;
	}else{
		sg90_con = 0;
	}
	
	if(cnt == 40){				//当溢出了40次,延时了20ms
		cnt = 0;  				
		sg90_con = 1;
	}		
}
 