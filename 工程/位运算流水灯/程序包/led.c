#include "reg52.h"

unsigned char i;

void Delay(unsigned int t)
{
	while(t--);
	while(t--);
}



void LEDRunning()
{
		
	for(i = 0; i < 8; i++)
	{
		P0 = ~(0x01 << i);
		Delay(60000);
	}

	
}

void main()
{
	while(1)
	{
		LEDRunning();
	}
}
