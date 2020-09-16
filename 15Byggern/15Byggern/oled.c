

#define OLED_COMMAND_ADDRESS 0x1000
#define OLED_DATA_ADDRESS 0x1200

#include <avr/pgmspace.h>
#include "fonts.h"
#include "oled.h"

static volatile char* oled_command_address = (char*)OLED_COMMAND_ADDRESS;
static volatile char* oled_data_address = (char*)OLED_DATA_ADDRESS;

POSITION position;

void write_command(uint8_t command){
	*oled_command_address = command;
}

void write_data(uint8_t data){
	*oled_data_address = data;
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
	
	//Page addressing
	write_command(0xb0);	//Page start address
	write_command(0x00);	//Lower nibble of column to 0
	write_command(0x10);	//Higher nibble of column
	

}

void oled_reset(){
	for(int line=0; line<8; line++){
		oled_clear_line(line);
	}
	oled_home();
}

void oled_home(){
	position.row=0;
	position.column=0;
}

void oled_goto_line(uint8_t line){
	
}

void oled_goto_column(uint8_t column){
	
}

void oled_clear_line(uint8_t line){
	for(int column=0; column<128; column++){
		
	}
	
	oled_home();
}

void oled_pos(uint8_t row, uint8_t column){
	position.row=row;
	position.column;
}

void oled_print(char* c){
	int out = c-32;
	for (int i=0; i<8; i++){
		write_data(&font8[out][i]);
	}
}