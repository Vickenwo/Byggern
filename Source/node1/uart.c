#include "uart.h"
#include <avr/io.h>


void USART_Init(unsigned int ubrr)
{
	UBRR0H = (unsigned int)(ubrr>>8);
	UBRR0L = (unsigned int) ubrr;
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
	
	fdevopen(USART_Transmit,USART_Receive);
}


void USART_Transmit(unsigned char data)
{
	
	while(!(UCSR0A & (1<<UDRE0)));
	
	UDR0 = data;
}

unsigned char USART_Receive(void)
{
	while (!(UCSR0A & (1<<RXC0)));
	
	return UDR0;
}

void USART_Print(unsigned char data)
{
	USART_Transmit(data);
	fdevopen(USART_Transmit,USART_Receive);
}