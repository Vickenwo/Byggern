#ifndef stdio.h
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#endif
#include "joystick.h"
#include "adc.h"
#include "can.h"
#include "settings.h"

volatile uint8_t BUTTON_PRESSED = 0;

void joystick_init()
{
	js.x_offset = adc_read(0)-127;
	js.y_offset = adc_read(1)-127;
	DDRE |= (0<<PE0);
}


int joystick_get_x_pos_prc()
{
	return js.x_pos_prc;
}

int joystick_get_y_pos_prc()
{
	return js.y_pos_prc;
}


DIRECTION joystick_get_direction()
{
	return js.dr;
}

int joystick_calculate_ratio(uint8_t input, uint8_t offset)
{
	int nom, sign, denom, result;
	nom = input-offset-127;
	sign = 1;
	if(nom < 0){sign = -1;}
	denom = 127-offset*sign;
	result = (double)nom/(double)denom*100.0;
	if(result > 100){result = 100;}
	return result;
}


int joystick_update_position_prc()
{
	int threshold = 5;
	int new_x = joystick_calculate_ratio(adc_read(0), js.x_offset);
	int new_y = joystick_calculate_ratio(adc_read(1), js.y_offset);
	
	if(new_x < js.x_pos_prc - threshold || new_x > js.x_pos_prc + threshold || new_y < js.y_pos_prc - threshold || new_y > js.y_pos_prc + threshold || BUTTON_PRESSED)
	{
		js.x_pos_prc = new_x;
		js.y_pos_prc = new_y;
		joystick_update_direction();
		
		return 1;
	}
	return 0;
}


void joystick_update_direction()
{
	uint8_t threshold = settings_get_sensitivity()*9;
	if((js.x_pos_prc > 0 + threshold)&&(abs(js.x_pos_prc)>=(abs(js.y_pos_prc)))){ js.dr = RIGHT; }
	else if((js.x_pos_prc < 0 - threshold)&&(abs(js.x_pos_prc)>=(abs(js.y_pos_prc)))){ js.dr = LEFT; }
	else if((js.y_pos_prc > 0 + threshold)&&(abs(js.x_pos_prc)<(abs(js.y_pos_prc)))){ js.dr = UP; }
	else if((js.y_pos_prc < 0 - threshold)&&(abs(js.x_pos_prc)<(abs(js.y_pos_prc)))){ js.dr = DOWN; }
	else{ js.dr = NEUTRAL; }
}


int slider_get_position_l()
{
	return sd.pos_l_prc;
}


int slider_get_position_r()
{
	return sd.pos_r_prc;
}


int slider_update_position_prc()
{
	int threshold = 5;
	int new_l = adc_read(2);
	int new_r = adc_read(3);
	
	if(abs(new_l-sd.pos_l)>threshold || abs(new_r-sd.pos_r)>threshold || slider_left_button_pressed()){
		sd.pos_l = new_l;
		sd.pos_r = new_r;
		sd.pos_l_prc = (sd.pos_l * 100)/255;
		sd.pos_r_prc = (sd.pos_r * 100)/255;
		return 1;
	}
	
	return 0;
}


int slider_right_button_pressed()
{
	if(PINB&(1<<PB0)){
		return 1;
	}
	return 0;

}

int slider_left_button_pressed()
{
	if(PINB&(1<<PB1)){
		return 1;
	}
	return 0;
}



void joystick_send()
{	
	MESSAGE joy;
	joy.length = 3;
	joy.data[0] = js.x_pos_prc+100;
	joy.data[1] = js.y_pos_prc+100;
	joy.data[2] = BUTTON_PRESSED;
	joy.id = JOYSTICK_ID;
	
	can_send(&joy);
	
	BUTTON_PRESSED=0;
	
}


void slider_send()
{
	MESSAGE slider;
	slider.length = 4;
	slider.data[0] = sd.pos_l_prc;
	slider.data[1] = sd.pos_r_prc;
	slider.data[2] = slider_left_button_pressed();
	slider.data[3] = slider_right_button_pressed();
	slider.id = SLIDER_ID;
	
	can_send(&slider);
}
