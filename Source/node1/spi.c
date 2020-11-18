#include "spi.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define DDR_SPI DDRB
#define DD_MISO PB6
#define DD_MOSI PB5
#define DD_SCK PB7
#define DD_SS PB4

void spi_select_slave()
{
	PORTB &= ~(1<<DD_SS);
}

void spi_deselect_slave()
{
	PORTB |= (1<<DD_SS);
}

void spi_init()
{
	/* Set MOSI and SCK output, all others input */
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK) | 1<< DD_SS;
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	/* Set SPI mode 0 */
	SPCR &= ~((1<<CPOL) | (1<<CPHA));
	
	//sei();
}


uint8_t spi_transmit(uint8_t data)
{
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	/* Return data register */
	return SPDR;
}