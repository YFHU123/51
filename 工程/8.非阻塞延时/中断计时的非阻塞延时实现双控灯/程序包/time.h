#ifndef __TIME_H__
#define __TIME_H__

#include <reg51.h>

//�ⲿ����������
extern unsigned int time1_cnt;
extern unsigned char time1_flag;
extern unsigned time1_enable;

extern unsigned int time2_cnt;
extern unsigned char time2_flag;
extern unsigned time2_enable;
//��������
void Timer0Init(void);

#endif