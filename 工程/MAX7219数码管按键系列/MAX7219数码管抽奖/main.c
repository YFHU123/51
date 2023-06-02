#include <reg52.h>
#include <seg.h>
#include <delay.h>

#define KEY_DELAY_TIME 100
#define KEY_LONG_TIME 1000
#define KEY_KEEP_TIME 50

sbit S1 = P1^0;

unsigned int key_val = 0;


unsigned char Date_buff[3] = {0, 0,0};//�������ʾ����������ֵ0xFFȷ������ʱ������
//��ʾ�����֣���ֵΪ10��ʱ����ʾ��-��


char Flag = 1; 
//char short_flag = 0;
int key_cnt1 = 0;
int key_cnt2 = 0;
void Key_scan()
{

	if(!S1)//����û����
	{
		Flag = 0;
		key_cnt1 = 0;
	}
	else if(!Flag)//���¼��
	{
		key_cnt1++;
		if(key_cnt1 > KEY_DELAY_TIME)
		{
			key_cnt1 = 0;
			key_val+=1;
			Flag = 1;
		}
	}
	else if(key_cnt1 < KEY_LONG_TIME)
	{
		key_cnt1++;
	}
	else
	{
		key_cnt2++;
		if(key_cnt2 > KEY_KEEP_TIME)
		{
			key_cnt2 = 0;
			key_val+=1;
			if(key_val > 9)
			{
				key_val = 0;
			}
		}
	}
}
//����ܡ�����Ϊ�𡱡�����������������λ
void 	Display_smg(unsigned char i) 
{
	write_data(1,i);   // ��ʾʱ���λ   
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


