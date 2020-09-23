#ifndef stdio.h
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#endif
#include "joystick.h"
#include "adc.h"

volatile uint8_t BUTTON_PRESSED = 0;

JOYSTICK joystick_init(){
	JOYSTICK *js;
	js->x_offset = adc_read(0)-127;
	js->y_offset = adc_read(1)-127 ;
	DDRE |= (0<<PE0);
	return *js;
}

void joystick_get_position(JOYSTICK *js){
	js->x_pos = adc_read(0);
	js->y_pos = adc_read(1);
	
	return;
}

int joystick_calculate_ratio(uint8_t input, uint8_t offset){
	
	int nom, sign, denom, result;
	nom = input-offset-127;
	sign = 1;
	if(nom < 0){sign = -1;}
	denom = 127-offset*sign;
	result = (double)nom/(double)denom*100.0;
	if(result > 100){result = 100;}
	return result;
}

void joystick_update_position_prc(JOYSTICK *js){
	js->x_pos_prc = joystick_calculate_ratio(adc_read(0), js->x_offset);
	js->y_pos_prc = joystick_calculate_ratio(adc_read(1), js->y_offset);
}

void joystick_update_direction(JOYSTICK *js){
	int threshold = 50;
	if((js->x_pos_prc > 0 + threshold)&&(abs(js->x_pos_prc)>=(abs(js->y_pos_prc)))){ js->dr = RIGHT; }
	else if((js->x_pos_prc < 0 - threshold)&&(abs(js->x_pos_prc)>=(abs(js->y_pos_prc)))){ js->dr = LEFT; }
	else if((js->y_pos_prc > 0 + threshold)&&(abs(js->x_pos_prc)<(abs(js->y_pos_prc)))){ js->dr = UP; }
	else if((js->y_pos_prc < 0 - threshold)&&(abs(js->x_pos_prc)<(abs(js->y_pos_prc)))){ js->dr = DOWN; }
	else{ js->dr = NEUTRAL; }
}

void joystick_print_direction(JOYSTICK *js){
	switch (js->dr)
	{
	case RIGHT:
		printf("RIGHT");
		break;
	case LEFT:
		printf("LEFT");
		break;
	case UP:
		printf("UP");
		break;
	case DOWN:
		printf("DOWN");
		break;
	case NEUTRAL:
		printf("NEUTRAL");
		break;
	}
}

void joystick_print_position(JOYSTICK *js){
	printf("(%d, %d)", js->x_pos_prc, js->y_pos_prc);
}

void joystick_print(JOYSTICK *js){
	
	int8_t x, y;
	x = js->x_pos_prc;
	y = js->y_pos_prc;
	
	
	char direction;
	switch (js->dr)
	{
		case RIGHT:
			direction = "RIGHT";
			break;
		case LEFT:
			direction = "LEFT";
			break;
		case UP:
			direction = "UP";
			break;
		case DOWN:
			direction = "DOWN";
			break;
		case NEUTRAL:
			direction = "NEUTRAL";
			break;
	}
	
	printf("X: %d\tY: %d\t Direction: %d\n\r", x, y, direction);
	//joystick_print_direction(js);
	
	//joystick_print_position();
	//joystick_get_direction();
}


SLIDER slider_get_position(){
	SLIDER sd;
	sd.pos_l = adc_read(2);
	sd.pos_r = adc_read(3);
	return sd;
}
