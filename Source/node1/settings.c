#include "settings.h"

/**
	@file
	@brief Implementation of settings of the menu
*/

settings stngs;

void settings_init()
{
	stngs.invert = 0;
	stngs.sensitivity = 5;
	stngs.brightness = 5;
	stngs.cursor = 0;
}

void settings_set_invert(uint8_t value)
{
	if(value == 0 || value == 1)
	{
		stngs.invert = value;
	}
}

uint8_t settings_get_invert()
{
	return stngs.invert;
}

void settings_set_sensitivity(uint8_t value)
{
	stngs.sensitivity = value;
}

uint8_t settings_get_sensitivity()
{
	return stngs.sensitivity;
}

void settings_set_brightness(uint8_t value)
{
	stngs.brightness = value;
}

uint8_t settings_get_brightness()
{
	return stngs.brightness;
}

void settings_set_cursor(uint8_t value)
{
	stngs.cursor = value;
}

uint8_t settings_get_cursor()
{
	return stngs.cursor;
}