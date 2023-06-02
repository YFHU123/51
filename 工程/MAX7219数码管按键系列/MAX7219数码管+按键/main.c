#include <reg52.h>
#include <seg.h>
#include <delay.h>

#define KEY_DELAY_TIME 100

sbit S1 = P1^0;

char n = 0;


unsigned char Date_buff[3] = {0, 0,0};//数码管显示缓冲区，初值0xFF确保启动时都不亮
//显示的数字，数值为10的时候，显示“-”


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


//数码管“以左为尊”————最左边是最高位
void 	Display_smg(unsigned char i) 
{
	write_data(8,i);   // 显示时最高位   
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
		Display_smg(n);
	}
}


