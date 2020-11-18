#include "game.h"
#include "can_controller.h"

void game_restart()
{
	in_game = 0;
	game_reset_score();
	game_reset_lives();
}

void game_init()
{
	in_game = 1;
	game_reset_score();
	game_reset_lives();
}

int game_get_in_game()
{
	return in_game;
}

void game_exit()
{
	in_game = 0;
	CAN_MESSAGE exit_game;
	exit_game.data_length = 2;
	exit_game.data[0] = EXIT;
	exit_game.data[1] = score;
	exit_game.id = GAME_STATE_ID;
	can_send(&exit_game,0);
	printf("SENT EXIT MESSAGE WITH ID %d\n\r", GAME_STATE_ID);
	game_reset_lives();
}

void game_send_lives()
{
	CAN_MESSAGE status;
	status.data_length = 1;
	status.data[0] = DECREASE_LIVES;
	status.id = GAME_STATE_ID;
	can_send(&status,0);
	printf("SENT STATUS MESSAGE WITH ID %d\n\r", GAME_STATE_ID);
}


void game_reset_lives()
{
	lives = 5;
}

void game_decrease_lives()
{
	lives -= 1;
	game_send_lives();
}

uint8_t game_get_lives()
{
	return lives;
}


void game_increase_score()
{
	score += 1;
}

void game_reset_score()
{
	score = 0;
}

int game_get_score()
{
	return score;
}