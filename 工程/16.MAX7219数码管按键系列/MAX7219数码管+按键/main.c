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
		Display_smg(n);
	}
}


