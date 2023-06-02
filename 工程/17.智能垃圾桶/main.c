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
 
void Timer0Init(void)		//500΢��@11.0592MHz
{
	//AUXR &= 0x7F;		
	TMOD &= 0xF0;	//���ö�ʱ��ģʽ16λ
	TMOD |= 0x01;	//���ö�ʱ��ģʽ
	TL0 = 0x33;		//���ö�ʱ����ʼֵ0.5ms
	TH0 = 0xFE;		//���ö�ʱ����ʼ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	ET0 = 1;		//�򿪶�ʱ��0�ж�
	EA  = 1;		//�����ж�EA
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
		//��ʱ�����㣬�Ա���һ�β��
		TH1 = 0;
		TL1 = 0;
	//1.�������Ͳ�:��Trig�˿�����10us�ĸߵ�ƽ
		startHC();
		//2. ��ʼ���Ͳ�:Echo�ɵ͵�ƽ��ת���ߵ�ƽ
		while(Echo == 0);
		//   ��ʼ���Ͳ���������ʱ��
		TR1 = 1;
		//3. ���շ��ز�:Echo�ɵ͵�ƽת�ظߵ�ƽ
		while(Echo == 1);
		//   ���շ��ز���ֹͣ��ʱ��
		TR1 = 0;
		//4. ����ʱ��
		time = (TH1 * 256 + TL1)*1.085;//us???
		//5. ���� = �ٶ� (340m/s)* ʱ��/2
		return  (time * 0.017);
}
 

 
void initSG90_0()
{
	angle = 1;      //��ʼ�Ƕ�0�ȣ�0.5ms�����1���Ǹߵ�ƽ
	cnt = 0;
	sg90_con = 1;//һ��ʼ�Ӹߵ�ƽ��ʼ
}
 
void openDustbin()
{
	char n;
	angle = 3; //90�ȣ�1.5ms�ߵ�ƽ
	//�������
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
	//�ظ�
	angle = 1; //0��
	angle_bak = angle;
	cnt = 0;
	Delay150ms();
}

 
void main()
{
	double dis;
	
	Timer0Init();
	Timer1Init();
	
	initSG90_0();//����ĳ�ʼλ��
	
	while(1){
		
		dis = get_distance();//���������
		if(dis < 10 ){
			//����
			openDustbin();
		}else{
			//�ظ�
			closeDustbin();
		}
	}
}
 
void Time0Handler() interrupt 1
{
	cnt++;  					//ͳ������Ĵ���
	//���¸���ֵ
	TL0 = 0x33;
	TH0 = 0xFE;
	
	//PWM����
	if(cnt < angle){
		sg90_con = 1;
	}else{
		sg90_con = 0;
	}
	
	if(cnt == 40){				//�������40��,��ʱ��20ms
		cnt = 0;  				
		sg90_con = 1;
	}		
}
 