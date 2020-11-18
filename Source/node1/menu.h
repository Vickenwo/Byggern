#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <util/delay.h>
#include "joystick.h"
#include "oled.h"

typedef enum{
	MENU, TEST, PLAY
}STATE;

STATE state;

typedef struct Menu
{
	char* title;
	char* sub_name;
	struct Menu* prev_menu;
	struct Menu** sub_menu;
	int num_subs;
	void (*fun_ptr)(void);
} Menu;


Menu* menu_create_sub_menu(char* title, char* sub_name, Menu* prev_menu, void (*function)(void));

void menu_init();

void menu_select_up();

void menu_select_down();

void menu_select();

void menu_action();

void menu_print();

void menu_run();

void menu_back();

void menu_color_invert();

void menu_cursor_swap();

void play_game();

void credits();

void poem();

void music();

void menu_calibrate();

void page_sensitivity();

void page_brightness();

void menu_print_scale(uint8_t value);

int menu_page_scale(uint8_t value, uint8_t direction);

#endif











































//#ifndef MENU_H
//#define MENU_H
//
//#include <stdio.h>
//#include <util/delay.h>
//#include "joystick.h"
//#include "oled.h"
//
//
//
//void menu_draw();
//void menu_update_selection();
//
//void sel1();
//void sel2();
//void sel3();
//
//
//void menu_input(DIRECTION dir);
//void menu_main(DIRECTION dir);
//
//void drawing(DIRECTION dir);
//
//#endif
//
//typedef enum{
	//MAIN_MENU, BACK, PRINT_MENU, PLAYERS_MENU, SETTINGS_MENU, 
	//}SELECTION;
//
//typedef struct
//{
	//char *title;
	//SELECTION **sub_menus;
	//uint8_t selected;
	//struct Menu *prev; 
	//struct Menu *next;
	//
//}Menu;
//
//Menu *new_menu(char *title, Menu *prev, uint8_t n_choices);
//void connect_sub_menu(Menu *menu, Menu **sub_menus);
//
//void draw_menu(Menu *menu);
//
//void menu_scroll_up(Menu *menu);
//void menu_scroll_down(Menu *menu);
//void menu_select(Menu *menu);
//
//
//
//
///*
//
//void create_menu(SELECTION selection[], uint8_t n_choices);
//
//void draw_menu(SELECTION selection[], uint8_t n_choices, uint8_t selected);
//
//*/