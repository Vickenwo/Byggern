#ifndef OLED_H
#define OLED_H

void oled_init();

void oled_white(uint8_t data);

void oled_fill();

void oled_black(uint8_t data);

void oled_clear();

void oled_home();

void oled_goto_line(uint8_t row);

void oled_goto_column(uint8_t column);

void oled_goto_pos(uint8_t row, uint8_t column);

void oled_clear_line(uint8_t line);

void oled_clear_column(uint8_t col);

void oled_print_char(char c);

void oled_print_heart();

void oled_print_lives(uint8_t lives);

void oled_brightness(int lvl);

void oled_print(char *string);

void oled_print_char_inverted(char c);

void oled_print_inverted(char *string);



#endif