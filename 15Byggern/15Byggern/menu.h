#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <util/delay.h>
#include "joystick.h"
#include "oled.h"



void menu_draw();
void menu_update_selection();

void sel1();
void sel2();
void sel3();


void menu_input(DIRECTION dir);
void menu_main(DIRECTION dir);

void drawing(DIRECTION dir);

#endif