

#define OLED_COMMAND_ADDRESS 0x1000
#define OLED_DATA_ADDRESS 0x1200

#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdio.h>
#include "fonts.h"
#include "oled.h"

static volatile char* oled_command_address = (char*)OLED_COMMAND_ADDRESS;
static volatile char* oled_data_address = (char*)OLED_DATA_ADDRESS;



void write_command(uint8_t command){
	oled_command_address[0] = command;
}

void write_data(uint8_t data){
	oled_data_address[0] = data;
}

void oled_white(uint8_t data){
	write_data(data);
}

void oled_black(uint8_t data){
	write_data(~data);
}

void (*color_sel_ptr_arr[])(uint8_t data) = {oled_white, oled_black};

void oled_fill(){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 127; j++){
			oled_goto_line(i);
			oled_goto_column(j);
			(*color_sel_ptr_arr[inverted])(0xFF);
		}
	}
	oled_home();
}


void oled_init(){
	//Display off
	write_command(0xae);
	
	//Re-map to 127
	write_command(0xa1);
	
	//Set COM Pins Hardware Configuration
	write_command(0xda);
	write_command(0x12);
	
	//Set COM output and Scan direction Remapped
	write_command(0xc8);
	
	//Set multiplex ratio
	write_command(0xa8);
	write_command(0x3f);
	
	//Set Clock/Oscillator Frequency
	write_command(0xd5);
	write_command(0x80);
	
	//Set Contrast Control
	write_command(0x81);
	write_command(0x50);
	
	//Set Pre Charge Period
	write_command(0xd9);
	write_command(0x21);
	
	//Set Memory Addressing Mode
	write_command(0x20);
	write_command(0x02);
	
	//Set Vcomh Deselect level
	write_command(0xdb);
	write_command(0x30);
	
	//Set external (1) or Internal(0) Iref
	write_command(0xad);
	write_command(0x00);
	
	//Resume to RAM content display
	write_command(0xa4);
	
	//Set Normal Display
	write_command(0xa6);
		
	//Display on
	write_command(0xaf);
	
	inverted = 0;
	oled_home();
}

void oled_clear(){
	for(int line=0; line<8; line++){
		oled_clear_line(line);
	}
	oled_home();
}

void oled_home(){
	//Set Column Address
	write_command(0x21);
	write_command(0x00);
	write_command(0x7f);
	//Set Page Address
	write_command(0x22);
	write_command(0x00);
	write_command(0x07);
}

void oled_goto_line(uint8_t row){
	position.row = row;
	
	//Set Page Address to selected row
	write_command(0x22);
	write_command(row);
	write_command(row+1);
}

void oled_goto_column(uint8_t column){
	position.column = column;
	
	//Set Column Address to selected column
	write_command(0x21);
	write_command(column);
	write_command(0x7f);
}

void oled_clear_line(uint8_t line){
	position.row = line;
	oled_goto_line(line);
	for(int column=0; column<128; column++){
		position.column=0;
		(*color_sel_ptr_arr[inverted])(0x00);
	}
	
	oled_home();
}

void oled_clear_column(uint8_t col){
	position.column = col;
	oled_goto_column(col);
	for(int line=0; line<8; line++){
		position.row=0;
		(*color_sel_ptr_arr[inverted])(0x00);
	}
	
	oled_home();
}

void oled_pos(uint8_t row, uint8_t column){
	oled_goto_line(row);
	oled_goto_column(column);
}


void oled_print_char(char c){
	int out = c-32;
	for (int i=0; i<8; i++){
		(*color_sel_ptr_arr[inverted])(pgm_read_byte(&font8[out][i]));
	}
}

void oled_print_anim(){
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			oled_pos(4,8);
			(*color_sel_ptr_arr[inverted])(pgm_read_byte(&sprite[i][j]));
		}
	}
}



void oled_brightness(int lvl){
	write_command(0x81);
	write_command(lvl);
}

void oled_print(char *string){
	/*
	for(int i = 0; string[i] != NULL; i++){
		oled_print_char(string[idx]);
		idx++;
		_delay_ms(1000);
	}
	*/
	
	while(*string != '\0'){
		
		oled_print_char(*string++);
		
		//_delay_ms(1000);
	}
	return;
}


