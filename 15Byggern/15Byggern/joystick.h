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

typedef struct{
	uint8_t pos_l, pos_r;
}SLIDER;

JOYSTICK joystick_init();
void joystick_get_position(JOYSTICK *js);
int joystick_calculate_ratio(uint8_t input, uint8_t offset);
void joystick_update_position_prc(JOYSTICK *js);
void joystick_update_direction(JOYSTICK *js);
void joystick_print_position(JOYSTICK *js);
void joystick_print_direction(JOYSTICK *js);

SLIDER slider_get_position();

#endif