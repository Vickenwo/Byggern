#include "joystick.h"

void joystick_init()
{
	js.x_pos = 100;
	js.y_pos = 100;
}

void joystick_update(uint8_t x, uint8_t y, uint8_t btn)
{
	js.x_pos = x;
	js.y_pos = y;
	js.button = btn;
	
	printf("x: %d, y: %d, btn: %d", js.x_pos, js.y_pos, js.button);
}

int joystick_get_x_pos()
{
	return js.x_pos-100;
}

int joystick_get_y_pos()
{
	return js.y_pos-100;
}

uint8_t joystick_get_btn()
{
	return js.button;
}

void joystick_set_btn(uint8_t value)
{
	js.button = value;
}

void slider_init()
{
	sd.pos_l=0;
	sd.pos_r=0;
}

void slider_update(uint8_t left, uint8_t right)
{
	sd.pos_l = left;
	sd.pos_r = right;
	printf("left: %d\n\r right:%d\n\r", sd.pos_l, sd.pos_r);
}

int slider_get_left()
{
	return sd.pos_l;
}

int slider_get_right()
{
	return sd.pos_r;
}