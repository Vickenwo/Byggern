/*
 * 15Byggern.c
 *
 * Created: 26.08.2020 19:38:07
 * Author : victortk
 */ 
#define F_CPU 4915200
#define FOSC 1843200
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#define BASE_ADDRESS 0x1000

#ifndef avr/io.h
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#endif
#include "uart.h"
#include <avr/interrupt.h>
#include "adc.h"
#include "joystick.h"




int main(void)
{
    /* Replace with your application code */
	USART_Init((MYUBRR));
	//USART_Print('A');
	DDRE |= (1 << PE1);
	PORTE |= (1 << PE1);	
	xmem_init();
	//SRAM_test();
	PWM_init();  
	
    while (1) 
    {
		printf("%d",adc_read(0));
		//printf("hello\n\r");
		
		
    }
}



void xmem_init(void){
	MCUCR |= (1 << SRE);
	SFIOR |= (1 << XMM2);
	DDRB &~(1<<PINB3);
}

void SRAM_test(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}

/*
void xmem_write(uint8_t data, uint16_t addr){
	volatile char *ext_mem = (*char) BASE_ADDRESS;
	ext_mem[addr] = data;
}

uint8_t xmem_read(uint16_t addr){
	volatile char *ext_mem = (char*) BASE_ADDRESS;
	uint8_t ret_val=ext_mem[addr];
	return ret_val;
}
*/