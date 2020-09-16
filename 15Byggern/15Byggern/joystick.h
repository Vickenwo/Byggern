
typedef struct{
	double x_pos, y_pos;
}JOYSTICK;

typedef struct{
	double pos_l, pos_r;
}SLIDER;

/*
enum DIRECTION{
	LEFT, RIGHT, UP, DOWN, NEUTRAL
} ;
*/
JOYSTICK joystick_get_position();
//DIRECTION joystick_get_direction();

uint8_t slider_get_position();
