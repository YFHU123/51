#include <reg52.h>
#include <seg.h>
#include <delay.h>

#define KEY_DELAY_TIME 100

sbit S1 = P1^0;
sbit S2 = P1^1;

char key_value = 0;


unsigned char Date_buff[3] = {0, 0,0};//数码管显示缓冲区，初值0xFF确保启动时都不亮
//显示的数字，数值为10的时候，显示“-”

char key1_flag = 1;
char key1_cnt;
char key2_flag = 1;
char key2_cnt;
void key_scan()
{
		if(S1)
		{
			key1_flag = 0;
			key1_cnt = 0;
		}
		else if(!key1_flag)
		{
			key1_cnt++;
			if(key1_cnt > KEY_DELAY_TIME)
			{
				key1_cnt = 0;
				if(!S2)
				{
					key1_flag = 1;
					key_value = 0;
					key_value -= 1;
				}
				key1_flag = 1;
				key_value+=1;
			}
		}
			
		if(S2)
		{
			key2_flag = 0;
			key2_cnt = 0;
		}
		else if(!key2_flag)
		{
			key2_cnt++;
			if(key2_cnt > KEY_DELAY_TIME)
			{
				key2_cnt = 0;
				key2_flag = 1;
				key_value-=1;
			}	
		}
		
		
}


//数码管“以左为尊”————最左边是最高位
void 	Display_smg(unsigned char i) 
{
	write_data(1,i%10);   // 显示时最高位
	write_data(2,i/10%10);
	write_data(3,i/100%10);
	write_data(4,i/1000%10);

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
		Display_smg(key_value);
	}
}


