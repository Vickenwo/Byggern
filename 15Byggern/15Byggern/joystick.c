#ifndef stdio.h
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#endif
#include "joystick.h"
#include "adc.h"


JOYSTICK joystick_get_position(){
	JOYSTICK js;
	js.x_pos = adc_read(0);
	js.y_pos = adc_read(1);
	return js;
}
/*
DIRECTION joystick_get_direction(){
	uint8_t x, y; //x = x_pos-x_neutral ; y = y_pos-y_neutral
	double threshold;
	if(abs(x)-threshold > 0 && abs(y)-threshold > 0) {
		return NEUTRAL;
	}
	if(abs(x) > abs(y)){
		if(x > 0){
			return RIGHT;
		} else {
			return LEFT;
		}
	} else if(y > 0){
		return UP;
	} else {
		return DOWN;
	}
	return 0;
}
*/
uint8_t slider_get_position(){
	return 0;
}
