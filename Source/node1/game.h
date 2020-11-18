#include <stdio.h>

typedef enum GAME_COMMAND
{
	NONE, EXIT, INIT, RESTART, DECREASE_LIVES
};

uint8_t in_game;
uint8_t score;
uint8_t lives;

void game_restart();

void game_init();

void game_reset_score();

void game_set_score(uint8_t value);

uint8_t game_get_score();

void game_reset_lives();

uint8_t game_get_lives();

void game_decrease_lives();

void game_check_lives();

void game_check_loss();

void game_play();

void game_finished();