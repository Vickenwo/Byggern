#include "menu.h"
#include "joystick.h"
#include "can.h"
#include "music.h"
#include "adc.h"

#include <stdlib.h>
#include <stdio.h>


Menu* main_menu;
Menu* current_menu;
int selected;
uint8_t menu_top = 1;
uint8_t in_function = 0;



Menu* menu_create_sub_menu(char* title, char* sub_name, Menu* prev_menu, void (*function)(void))
{
	Menu* new_menu = malloc(sizeof(Menu));
	new_menu->title = title;
	new_menu->sub_name = sub_name;
	new_menu->prev_menu = prev_menu;
	new_menu->sub_menu = NULL;
	new_menu->num_subs = 0;
	new_menu->fun_ptr = function;
	
	prev_menu->num_subs += 1;
	int ns = prev_menu->num_subs;
	prev_menu->sub_menu = realloc(prev_menu->sub_menu, sizeof(Menu*)*ns);
	prev_menu->sub_menu[ns-1] = new_menu;
	return new_menu;
}

void menu_init()
{
	main_menu = malloc(sizeof(Menu));
	main_menu->title = "MAIN MENU";
	main_menu->sub_name = NULL;
	main_menu->prev_menu = NULL;
	main_menu->sub_menu = NULL;
	main_menu->num_subs = 0;
	main_menu->fun_ptr = NULL;
	current_menu = main_menu;
	selected = 1;
	
	Menu* play_entry = menu_create_sub_menu("PLAY GAME", "Play Game", main_menu, &play_game);
	Menu* settings_menu = menu_create_sub_menu("SETTINGS", "Settings", main_menu, NULL);
	Menu* credits_entry = menu_create_sub_menu("CREDITS", "Credits", main_menu, &credits);
	Menu* poem_entry = menu_create_sub_menu("POEM", "Poem", main_menu, &poem);
	//Menu* music_menu = menu_create_sub_menu("MUSIC", "Music", main_menu, &music);
	
	
	// SETTINGS
	Menu* invert = menu_create_sub_menu("INVERT COLORS", "Invert Colors", settings_menu, &menu_color_invert);
	Menu* sensitivity = menu_create_sub_menu("SENSITIVITY", "Sensitivity", settings_menu, &page_sensitivity);
	Menu* brightness = menu_create_sub_menu("BRIGHTNESS", "Brightness", settings_menu, &page_brightness);
	Menu* calibrate = menu_create_sub_menu("CALIBRATE", "Calibrate", settings_menu, &menu_calibrate);
	Menu* cursor = menu_create_sub_menu("CURSOR", "Change Cursor", settings_menu, &menu_cursor_swap);
	
	Menu* back = menu_create_sub_menu("BACK", "Back", settings_menu, &menu_back);

	menu_print();
}


void menu_select_up()
{
	if(selected > 1)
	{
		selected -= 1;
		if(selected < menu_top)
		{
			menu_top = selected;
		}
		menu_print();
	}
}

void menu_select_down()
{
	if(selected < current_menu->num_subs)
	{
		selected += 1;
		if(selected-3 > menu_top)
		{
			menu_top = selected-3;
		}
		
		menu_print();
	}
}

void menu_select()
{
	if(current_menu->sub_menu[selected-1]->sub_menu != NULL)
	{
		current_menu = current_menu->sub_menu[selected-1];
		selected = 1;
		menu_top = 1;
		menu_print();
	}
	else
	{
		menu_action();
	}
}

void menu_action()
{
	(*current_menu->sub_menu[selected-1]->fun_ptr)();
}

void menu_print()
{
	printf(current_menu->title);
	
	
	oled_clear();
	
	oled_goto_pos(1,1);
	oled_print(current_menu->title);
	
	oled_goto_pos(2,1);
	oled_print("----------------");
	
	
	
	for(uint8_t i = 0; i < 4; i++)
	{
		if(menu_top + i <= current_menu->num_subs)
		{
			oled_goto_pos(i+3,8);
			if(menu_top + i == selected)
			{
				if(settings_get_cursor())
				{
					oled_print_inverted(current_menu->sub_menu[menu_top+i-1]->sub_name);
				}
				else
				{
					oled_goto_pos(i+3,0);
					oled_print(">");
					oled_print(current_menu->sub_menu[menu_top+i-1]->sub_name);
				}
			}
			else
			{
				oled_print(current_menu->sub_menu[menu_top+i-1]->sub_name);
			}
		}
	}
}


void menu_run()
{
	switch(joystick_get_direction())
	{
		case UP:
			menu_select_up();
			_delay_ms(1000);
			break;
			
		case DOWN:
			menu_select_down();
			_delay_ms(1000);
			break;
		
		default:
			break;
	}
	if(BUTTON_PRESSED)
	{
		
		BUTTON_PRESSED = 0;
		menu_select();
	}
}


void menu_color_invert()
{
	_delay_ms(10);
	if(settings_get_invert())
	{
		settings_set_invert(0);
	}
	else
	{
		settings_set_invert(1);
	}
	menu_print();
}

void menu_cursor_swap()
{
	_delay_ms(10);
	if(settings_get_cursor())
	{
		settings_set_cursor(0);
	}
	else
	{
		settings_set_cursor(1);
	}
	menu_print();
}

void play_game()
{
	game_init();
	state = PLAY;
}

void menu_back()
{
	current_menu = current_menu->prev_menu;
	selected = 1;
	menu_top = 1;
	menu_print();
}

void credits()
{
	
	oled_clear();
	oled_goto_pos(0,1);
	oled_print("~~~  CREDITS ~~~");
	
	oled_goto_pos(2,1);
	oled_print("Special thanks");
	oled_goto_pos(3,55);
	oled_print("to");
	oled_goto_pos(4,1);
	oled_print("Eivind & Asgeir");
	oled_goto_pos(5,50);
	oled_print_heart();
	oled_print_heart();
	oled_print_heart();
	oled_goto_pos(7,55);
	oled_print_inverted("Ok");
	
	music_PWM_init();
	music_play();
	PWM_init();
	
	while (1)
	{
		if(BUTTON_PRESSED)
		{
			
			break;
		}
	}
	
	menu_print();
	BUTTON_PRESSED = 0;
}

void poem()
{
	in_function = 1;
	oled_clear();
	
	oled_goto_pos(1,1);
	oled_print("~~~~~ POEM ~~~~~");
	oled_goto_pos(3,1);
	oled_print("Roses are red");
	oled_goto_pos(4,1);
	oled_print("Violets are blue");
	oled_goto_pos(5,1);
	oled_print("Byggern is done");
	oled_goto_pos(7,1);
	oled_print_inverted("Back to MainMenu");
	while(1)
	{
		if(BUTTON_PRESSED)
		{
			break;
		}
	}
	menu_print();
	BUTTON_PRESSED = 0;
}

//void music()
//{
	//music_PWM_init();
	//music_play();
	//music_PWM_init();
//}

void menu_calibrate()
{
	MESSAGE cal;
	cal.length = 1;
	cal.data[0] = 1;
	cal.id = CALIBRATE_ID;
	can_send(&cal);
}


void menu_print_scale(uint8_t value)
{
	oled_clear_line(4);
	oled_goto_pos(4,0);
	oled_print("Value:");
	
	for(uint8_t i = 0; i < 11-value; i++)
	{
		oled_print_inverted(" ");
	}
}

int sensitivity_scale(uint8_t value)
{
	uint8_t sensitivity = settings_get_sensitivity();
	settings_set_sensitivity(5);
	
	oled_clear();
	oled_goto_line(1);
	oled_print(current_menu->sub_menu[selected-1]->title);
	oled_goto_line(2);
	oled_print("----------------");
	
	menu_print_scale(value);
	
	oled_goto_pos(7,56);
	oled_print_inverted("OK");
	
	while(1)
	{
		joystick_update_position_prc();
		
		joystick_update_direction();
		switch(joystick_get_direction())
		{
			case LEFT:
				if(value < 10)
				{
					value += 1;
					menu_print_scale(value);
				}
			
			
				break;
			case RIGHT:
				if(value > 1)
				{
					value -= 1;
					menu_print_scale(value);
				}
				
				break;
			default:
				break;
		}
		
		if(BUTTON_PRESSED)
		{
			break;
		}
	}
	settings_set_sensitivity(sensitivity);
	BUTTON_PRESSED = 0;
	return value;
}


int brightness_scale(uint8_t value)
{
	uint8_t sensitivity = settings_get_sensitivity();
	settings_set_sensitivity(5);
	
	oled_clear();
	oled_goto_line(1);
	oled_print(current_menu->sub_menu[selected-1]->title);
	oled_goto_line(2);
	oled_print("----------------");
	
	menu_print_scale(11-value);
	
	oled_goto_pos(7,56);
	oled_print_inverted("OK");
	
	while(1)
	{
		joystick_update_position_prc();
		
		joystick_update_direction();
		switch(joystick_get_direction())
		{
			case RIGHT:
				if(value < 10)
				{
					value += 1;
					oled_brightness(value);
					menu_print_scale(11-value);
				}
			
			
				break;
			case LEFT:
				if(value > 1)
				{
					value -= 1;
					oled_brightness(value);
					menu_print_scale(11-value);
				}
			
				break;
			default:
				break;
		}
		
		if(BUTTON_PRESSED)
		{
			break;
		}
	}
	settings_set_sensitivity(sensitivity);
	BUTTON_PRESSED = 0;
	return value;
}


void page_brightness()
{
	settings_set_brightness(brightness_scale(settings_get_brightness()));
	menu_print();
}

void page_sensitivity()
{
	settings_set_sensitivity(sensitivity_scale(settings_get_sensitivity()));
	menu_print();
}
