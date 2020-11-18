#ifndef JOYSTICK_H
#define JOYSTICK_H

volatile uint8_t BUTTON_PRESSED;

typedef enum{
	LEFT, RIGHT, UP, DOWN, NEUTRAL
}DIRECTION;


typedef struct{
	uint8_t x_pos, y_pos;
	int x_pos_prc, y_pos_prc, x_offset, y_offset;
	DIRECTION dr;
	
}JOYSTICK;

JOYSTICK js;


typedef struct{
	uint8_t pos_l, pos_r, pos_l_prc, pos_r_prc, left_button, right_button;
}SLIDER;

SLIDER sd;

void joystick_init();

int joystick_get_x_pos_prc();

int joystick_get_y_pos_prc();

DIRECTION joystick_get_direction();

int joystick_calculate_ratio(uint8_t input, uint8_t offset);

int joystick_update_position_prc();

void joystick_update_direction();

int slider_get_position_l();

int slider_get_position_r();

int slider_update_position_prc();

int slider_right_button_pressed();
int slider_left_button_pressed();

void joystick_send();

void slider_send();

#endif