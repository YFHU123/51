#include "reg52.h"
#include "uart.h"
void main()
{
	u8 i;
	UART_Init();
	while(1)
	{
			UART_Send_Data(UART_Receive_Data());
	}
}
