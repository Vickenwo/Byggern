#include <stdio.h>

typedef struct 
{
	uint8_t x_pos, y_pos, button;
}Joystick;

typedef struct{
	uint8_t pos_l, pos_r;
}Slider;

Joystick js;
Slider sd;
void joystick_init();

void joystick_update(uint8_t x, uint8_t y, uint8_t btn);

int joystick_get_x_pos();
int joystick_get_y_pos();
uint8_t joystick_get_btn();
void joystick_set_btn(uint8_t value);

void slider_init();
void slider_update(uint8_t left, uint8_t right);
int slider_get_left();
int slider_get_right();