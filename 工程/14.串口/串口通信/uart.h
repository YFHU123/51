#ifndef __UART__
#define __UART__

typedef unsigned char u8;

void UART_Init();
void UART_Send_Data(u8 byte);
u8 UART_Receive_Data();

#endif
