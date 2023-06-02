#include <reg52.h>
#include <seg.h>
#include <delay.h>

#define KEY_DELAY_TIME 100
#define KEY_LONG_TIME 1000
#define KEY_KEEP_TIME 50

sbit S1 = P1^0;

unsigned int key_val = 0;


unsigned char Date_buff[3] = {0, 0,0};//数码管显示缓冲区，初值0xFF确保启动时都不亮
//显示的数字，数值为10的时候，显示“-”


char Flag = 1; 
//char short_flag = 0;
int key_cnt1 = 0;
int key_cnt2 = 0;
void Key_scan()
{

	if(!S1)//按键没按下
	{
		Flag = 0;
		key_cnt1 = 0;
	}
	else if(!Flag)//按下检测
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
//数码管“以左为尊”————最左边是最高位
void 	Display_smg(unsigned char i) 
{
	write_data(1,i);   // 显示时最高位   
    // 显示时最低位
}

void main(void)
{
	
	
  unsigned char i;
  init_max7221();    // 初始化
  delayms(2);
  for(i = 0; i < 8; i++)
  {
		write_data(i+1,10);   // 显示-位
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


