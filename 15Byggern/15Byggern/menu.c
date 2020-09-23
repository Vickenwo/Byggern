#include "menu.h"

// draw menu
char menu_opt1[] = "Option 1";
char menu_opt2[] = "Invert";
char menu_opt3[] = "Settings";
char menu_sel[] = ">";

unsigned char sel_idx = 0;


void menu_draw(){
	oled_clear();
	oled_goto_line(0);
	oled_goto_column(16);
	oled_print(menu_opt1);
	oled_goto_line(1);
	oled_goto_column(16);
	oled_print(menu_opt2);
	oled_goto_line(2);
	oled_goto_column(16);
	oled_print(menu_opt3);
	menu_update_selection();
}

void menu_update_selection(){
	for(uint8_t i = 0; i < 8; i++){
		oled_clear_column(i);
	}
	oled_pos(sel_idx,0);
	oled_print(menu_sel);
}


void sel1(){
	printf("Option: 1\n\r");
}
void sel2(){
	printf("Inverting\n\r");
	if(inverted){inverted = 0;} else {inverted = 1;}
	menu_draw();
}
void sel3(){
	printf("Option: 3\n\r");
}


void (*menu_sel_ptr_arr[])() = {sel1, sel2, sel3};


void menu_input(DIRECTION dir){
	switch (dir){
			break;
		case UP:
			// decrease idx
			if(sel_idx != 0){
				sel_idx--;
				
				menu_update_selection();
				_delay_ms(1000);
			}
			break;
		case DOWN:
			// increase idx
			if(sel_idx+1 <= 2){
				sel_idx++;
				
				menu_update_selection();
				_delay_ms(1000);
			}
			break;
	}
}

void menu_main(DIRECTION dir){
	menu_input(dir);
	if(BUTTON_PRESSED){
		BUTTON_PRESSED = 0;
		(*menu_sel_ptr_arr[sel_idx])();
	}
}