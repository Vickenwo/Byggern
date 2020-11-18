#ifndef UART_H
#define UART_H


void USART_Init(unsigned int ubrr);

void USART_Transmit(unsigned char data);

unsigned char USART_Receive(void);

void USART_Print(unsigned char data);
#endif
