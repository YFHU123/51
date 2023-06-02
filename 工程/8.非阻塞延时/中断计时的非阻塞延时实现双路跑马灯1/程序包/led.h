#ifndef __LED_H__
#define __LED_H__

#include <reg51.h>
#include "time.h"
#include <intrins.h>


sbit P00 = P0^0;
sbit P01 = P0^1;
sbit P02 = P0^2;
sbit P03 = P0^3;

sbit P04 = P0^4;
sbit P05 = P0^5;
sbit P06 = P0^6;
sbit P07 = P0^7;


#define LED1_SHINE_TIME 1000;
#define LED2_SHINE_TIME 1000;

//º¯ÊýÉùÃ÷
void led_init();
void led1_task();
void led2_task();


#endif