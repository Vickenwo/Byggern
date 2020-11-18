#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdio.h>

/**
 *@file
 *@brief The setting function for menu
*/

typedef struct settings
{
	uint8_t invert;
	uint8_t sensitivity;
	uint8_t brightness;
	uint8_t cursor;
}settings;

/**
 *@brief
*/
void settings_init();

/**
 *@brief
 *@param
*/
void settings_set_invert(uint8_t value);
/**
 *@brief
 *@return
*/
uint8_t settings_get_invert();

/**
 *@brief
 *@param
*/
void settings_set_sensitivity(uint8_t value);

/**
 *@brief
 *@return
*/
uint8_t settings_get_sensitivity();

/**
 *@brief
 *@param
*/
void settings_set_brightness(uint8_t value);
/**
 *@brief
 *@return
*/
uint8_t settings_get_brightness();

void settings_set_cursor(uint8_t value);
/**
 *@brief
 *@return
*/
uint8_t settings_get_cursor();

#endif