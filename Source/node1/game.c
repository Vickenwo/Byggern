#include <util/delay.h>
#include "game.h"
#include "oled.h"
#include "can.h"
#include "joystick.h"

MESSAGE game_msg;

void game_restart()
{
	in_game = 0;
	score = 0;
	MESSAGE game_msg;
	game_msg.length = 1;
	game_msg.data[0] = RESTART;
	game_msg.id = GAME_STATE_ID;
	can_send(&game_msg);
}

void game_init()
{
	in_game = 1;
	score = 0;
	game_reset_lives();
	MESSAGE game_msg;
	game_msg.length = 1;
	game_msg.data[0] = INIT;
	game_msg.id = GAME_STATE_ID;
	can_send(&game_msg);
	
	oled_clear();
	oled_goto_pos(2,0);
	oled_print("PLAYING GAME");
	oled_print_lives(lives);
}

void game_reset_score()
{
	score = 0;
}

void game_set_score(uint8_t value)
{
	
	score = value;
}

uint8_t game_get_score()
{
	uint8_t score;
	can_receive(&game_msg);
	if(game_msg.id = 4){
		game_msg.data[0] = score;
	}
	return score;
}

void game_reset_lives()
{
	lives = 5;
}

void game_decrease_lives()
{
	lives -= 1;
	oled_print_lives(lives);
}

uint8_t game_get_lives()
{
	return lives;
}

void game_check_lives()
{
	can_receive(&game_msg);
	if(game_msg.id == GAME_STATE_ID && game_msg.data[0] == DECREASE_LIVES)
	{
		game_decrease_lives();
		game_msg.data[0] = NONE;
	}
}

void game_check_loss()
{
	can_receive(&game_msg);
	if(game_msg.id == GAME_STATE_ID && game_msg.data[0] == EXIT)
	{
		game_set_score(game_msg.data[1]);
		game_msg.data[0] = NONE;
		in_game = 0;
	}
}

void game_play()
{
	
}

void game_finished()
{
	oled_clear();
	oled_goto_pos(1,0);
	oled_print("GAME OVER");

	while(1)
	{
		if(BUTTON_PRESSED)
		{
			_delay_ms(100);
			BUTTON_PRESSED = 0;
			_delay_ms(100);
			break;
		}
	}
}