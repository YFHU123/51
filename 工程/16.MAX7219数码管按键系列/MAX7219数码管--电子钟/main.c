#include <reg52.h>
#include <seg.h>
#include <delay.h>

#define KEY_DELAY_TIME 100

sbit S1 = P1^0;

char n = 0;


unsigned char Date_buff[3] = {0, 0,0};//�������ʾ����������ֵ0xFFȷ������ʱ������
//��ʾ�����֣���ֵΪ10��ʱ����ʾ��-��


char flag_key;
char cnt_key;
void key_scan()
{
	if(S1 == 1)
		{
			flag_key = 1;
			cnt_key = 0;
		}
		if(flag_key == 1&& S1==0)
		{
			cnt_key++;
			if(cnt_key > KEY_DELAY_TIME)
			{
				cnt_key = 0;
				n+=1;
				flag_key = 0;
				if(n == 10)
					n = 0;
			}
			
		}
}


void InitTimer0()
{
	TMOD = 0x01;
	TH0 = (65535 - 50000) / 256; // 50ms
	TL0 = (65535 - 50000) % 256;
	
	ET0 = 1;
	EA = 1;
	TR0 = 1;
}

unsigned char count = 0;
unsigned char sec = 0;
unsigned char min = 0;
unsigned char hour = 0;
void ServiceTimer0() interrupt 1
{
	TH0 = (65535 - 50000) / 256;
	TL0 = (65535 - 50000) % 256;
	
	count++;
	if(count == 20)//1s
	{
		count = 0;
		sec++;
		if(sec == 60)
		{
			sec = 0;
			min++;
			if(min == 60)
			{
				min = 0;
				hour ++;
				if(hour == 24)
				{
					hour = 0;
				}
			}
		}
	}
}


//����ܡ�����Ϊ�𡱡�����������������λ
void 	Display_smg() 
{
	write_data(1,sec%10);   
	write_data(2,sec/10);
	write_data(4,min%10);
	write_data(5,min/10);
	write_data(7,hour%10);
	write_data(8,hour/10);
}

void main(void)
{
  unsigned char i;
  init_max7221();    // ��ʼ��
	InitTimer0();
  delayms(2);
  for(i = 0; i < 8; i++)
  {
		write_data(i+1,10);   // ��ʾ-λ
  }
  delayms(1000);
  while(1) 
	{
		//key_scan();	
		Display_smg();
	}
}


