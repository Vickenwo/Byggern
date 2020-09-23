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
#include <avr/sleep.h>
#endif
#include "uart.h"
#include <avr/interrupt.h>
#include "adc.h"
#include "joystick.h"
#include "oled.h"
#include "menu.h"

typedef enum{
	MENU, TEST
}STATE;

STATE state;

JOYSTICK js;
SLIDER sd;

void init(){
	USART_Init((MYUBRR));
	xmem_init();
	PWM_init();
	oled_init();
	
	DDRE |= (1 << PE1);
	PORTE |= (1 << PE1);
	
	cli();
	EMCUCR |= (1<<ISC2);
	GICR |= (1<<INT2);
	sei();
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);
	
	JOYSTICK js = joystick_init();
	SLIDER sd = slider_get_position();
	
	oled_brightness(5);
	inverted = 0;
	state = MENU;
	menu_draw();
}

int main(void){
	
	init();
	
	while(1){
		switch(state){
			case MENU:
				joystick_update_position_prc(&js);
				joystick_update_direction(&js);
				menu_main(js.dr);
				//_delay_ms(20);
				break;
			case TEST:
				
				
				break;
		}
	}
	
}


ISR(INT2_vect){
	BUTTON_PRESSED = 1;
}


void xmem_init(void){
	MCUCR |= (1 << SRE);
	SFIOR |= (1 << XMM2);
	DDRB &~(1<<PINB3);
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