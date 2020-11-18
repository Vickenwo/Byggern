

#define OLED_COMMAND_ADDRESS 0x1000
#define OLED_DATA_ADDRESS 0x1200

#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdio.h>
#include "fonts.h"
#include "oled.h"
#include "settings.h"

static volatile char* oled_command_address = (char*)OLED_COMMAND_ADDRESS;
static volatile char* oled_data_address = (char*)OLED_DATA_ADDRESS;


void oled_init()
{
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
	
	oled_brightness(settings_get_brightness());
	
	oled_home();
}

void write_command(uint8_t command)
{
	oled_command_address[0] = command;
}

void write_data(uint8_t data)
{
	oled_data_address[0] = data;
}

void oled_white(uint8_t data)
{
	write_data(data);
}

void oled_black(uint8_t data)
{
	write_data(~data);
}

void (*color_sel_ptr_arr[])(uint8_t data) = {oled_white, oled_black};

void oled_fill()
{
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 127; j++)
		{
			oled_goto_line(i);
			oled_goto_column(j);
			(*color_sel_ptr_arr[settings_get_invert()])(0xFF);
		}
	}
	oled_home();
}


void oled_clear()
{
	for(int line=0; line<8; line++)
	{
		oled_clear_line(line);
	}
	oled_home();
}

void oled_home()
{
	//Set Column Address
	write_command(0x21);
	write_command(0x00);
	write_command(0x7f);
	//Set Page Address
	write_command(0x22);
	write_command(0x00);
	write_command(0x07);
}

void oled_goto_line(uint8_t row)
{
	//Set Page Address to selected row
	write_command(0x22);
	write_command(row);
	write_command(row+1);
}

void oled_goto_column(uint8_t column)
{
	//Set Column Address to selected column
	write_command(0x21);
	write_command(column);
	write_command(0x7f);
}

void oled_goto_pos(uint8_t row, uint8_t column)
{
	oled_goto_line(row);
	oled_goto_column(column);
}

void oled_clear_line(uint8_t line)
{
	oled_goto_pos(line,0);
	for(int column=0; column<128; column++)
	{
		(*color_sel_ptr_arr[settings_get_invert()])(0x00);
	}
	
	oled_home();
}

void oled_clear_column(uint8_t col)
{
	for(int line=0; line<8; line++)
	{
		oled_goto_pos(line,col);
		(*color_sel_ptr_arr[settings_get_invert()])(0x00);
	}
	
	oled_home();
}


void oled_print_char(char c)
{
	int out = c-32;
	for (int i=0; i<8; i++)
	{
		(*color_sel_ptr_arr[settings_get_invert()])(pgm_read_byte(&font8[out][i]));
	}
}

void oled_print_heart()
{
	for (int i=0; i<8; i++)
	{
		(*color_sel_ptr_arr[settings_get_invert()])(pgm_read_byte(&symbols[4][i]));
	}
}


void oled_print_lives(uint8_t lives)
{
	oled_clear_line(4);
	oled_goto_pos(4,25);
	for(uint8_t i; i<lives; i++)
	{
		oled_print_heart();
		oled_print(" ");
	}
}

void oled_brightness(int lvl)
{
	write_command(0x81);
	write_command(25*lvl);
}

void oled_print(char *string)
{
	while(*string != '\0'){
		
		oled_print_char(*string++);
	}
	return;
}

void oled_print_char_inverted(char c)
{
	int out = c-32;
	uint8_t inv = 0;
	if(settings_get_invert() == 0)
	{
		inv = 1;
	}
	for (int i=0; i<8; i++){
		(*color_sel_ptr_arr[inv])(pgm_read_byte(&font8[out][i]));
	}
}

void oled_print_inverted(char *string)
{
	while(*string != '\0')
	{
		oled_print_char_inverted(*string++);
	}
	return;
}