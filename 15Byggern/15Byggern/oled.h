#ifndef OLED_H
#define OLED_H

typedef struct{
	uint8_t row, column;
}POSITION;

POSITION position;

uint8_t inverted;

void oled_init();

void oled_white(uint8_t data);

void oled_fill();

void oled_black(uint8_t data);

void oled_clear();

void oled_home();

void oled_goto_line(uint8_t row);

void oled_goto_column(uint8_t column);

void oled_clear_line(uint8_t line);

void oled_clear_column(uint8_t col);

void oled_pos(uint8_t row, uint8_t column);

void oled_print_char(char c);

void oled_print_anim();

void oled_brightness(int lvl);

void oled_print(char *string);

void oled_create_image(char** in);

#endif