#include <reg52.h>
#include <seg.h>
#include <delay.h>

//#define KEY_DELAY_TIME 100
#define KEY_SHORT_TIME 100
#define KEY_LONG_TIME 1000

sbit S1 = P1^0;

unsigned int key_val = 0;


unsigned char Date_buff[3] = {0, 0,0};//�������ʾ����������ֵ0xFFȷ������ʱ������
//��ʾ�����֣���ֵΪ10��ʱ����ʾ��-��


char Flag = 0; 
char short_flag = 0;
int key_cnt = 0;
void Key_scan()
{

	if(S1 == 1)
	{
		Flag = 1;
		key_cnt = 0;
		if(short_flag)
		{
			short_flag = 0;
			key_val += 1;
			if(key_val > 9)
			{
				key_val = 0;
			}
		}
	}
	if(Flag == 1 && S1 == 0)
	{
		key_cnt++;
		if(key_cnt > KEY_SHORT_TIME)
		{
			short_flag = 1;
		}
		if(key_cnt > KEY_LONG_TIME)
		{
			short_flag = 0;
			key_cnt = 0;
			Flag = 0;
			key_val = 0;
		}	
	}
}
//����ܡ�����Ϊ�𡱡�����������������λ
void 	Display_smg(unsigned char i) 
{
	write_data(8,i);   // ��ʾʱ���λ   
    // ��ʾʱ���λ
}

void main(void)
{
	
	
  unsigned char i;
  init_max7221();    // ��ʼ��
  delayms(2);
  for(i = 0; i < 8; i++)
  {
		write_data(i+1,10);   // ��ʾ-λ
  }
  delayms(1000);
  while(1) 
	{
//		if(S1 == 1)
//		{
//			flag_key = 1;
//		}
//		if(flag_key == 1&& S1==0)
//		{
//			n+=1;
//			flag_key = 0;
//		}
		key_scan();	
		Display_smg(key_val);
	}
}


