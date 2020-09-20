
typedef struct{
	uint8_t row, column;
}POSITION;

void oled_init();

void oled_reset();

void oled_home();

void oled_goto_line(uint8_t row);

void oled_goto_column(uint8_t column);

void oled_clear_line(uint8_t line);

void oled_pos(uint8_t row, uint8_t column);

void oled_print(char c);

void oled_brightness(int lvl);


