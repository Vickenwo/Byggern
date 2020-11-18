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
#include <avr/interrupt.h>
#endif
#include "uart.h"
#include "spi.h"
#include "adc.h"
#include "joystick.h"
#include "oled.h"
#include "menu.h"
#include "mcp2515.h"
#include "can.h"
#include "settings.h"
#include "music.h"
#include "game.h"

void init()
{
	USART_Init((MYUBRR));
	xmem_init();
	PWM_init();
	oled_init();
	can_init();
	settings_init();
	menu_init();
	game_restart();
	
	DDRE |= (1 << PB1);
	DDRE |= (1 << PE1);
	PORTE |= (1 << PE1);
	
	cli();
	EMCUCR |= (1<<ISC2);
	GICR |= (1<<INT2);
	sei();
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);
	
	joystick_init();
	
	oled_brightness(5);
	state = MENU;
}

int main(void)
{

	init();

	while(1)
	{
		switch(state)
		{
			case TEST:
				//music_PWM_init();
				//music_play();
				break;
				
			case MENU:
				joystick_update_position_prc();
				menu_run();
				
				break;
				
			case PLAY:
				if(in_game)
				{
					game_check_lives();
					game_check_loss();
					
					if(joystick_update_position_prc())
					{
						joystick_send();
						_delay_ms(100);
					}
					if(slider_update_position_prc())
					{
						slider_send();
						_delay_ms(100);

					}
				}
				else
				{
					game_finished();
					
					state = MENU;
					menu_print();
				}
		
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



//void xmem_write(uint8_t data, uint16_t addr){
	//volatile char *ext_mem = (*char) BASE_ADDRESS;
	//ext_mem[addr] = data;
//}
//
//
//uint8_t xmem_read(uint16_t addr){
	//volatile char *ext_mem = (char*) BASE_ADDRESS;
	//uint8_t ret_val=ext_mem[addr];
	//return ret_val;
//}
