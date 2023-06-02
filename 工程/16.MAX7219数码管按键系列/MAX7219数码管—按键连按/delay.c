#include "delay.h"

void delayms(unsigned int x)
{
    unsigned char i;
    while(x--)
    {
        for(i = 0; i < 120; i++);
    }
}