#include <stdio.h>

typedef enum GAME_COMMAND
{
	NONE, EXIT, INIT, RESTART, DECREASE_LIVES
};

uint8_t in_game;
uint8_t lives;
uint8_t score;

void game_restart();

void game_init();

int game_get_in_game();

void game_exit();

void game_reset_lives();

void game_decrease_lives();

uint8_t game_get_lives();

void game_increase_score();

void game_send_lives();

void game_reset_score();

int game_get_score();