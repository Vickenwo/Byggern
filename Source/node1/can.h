#ifndef CAN_H
#define CAN_H

#include <stdint.h>

typedef struct{
	uint8_t id, data[8], length;
}MESSAGE;

typedef enum CAN_ID 
{
	CALIBRATE_ID, JOYSTICK_ID, SLIDER_ID, GAME_STATE_ID
};

void can_init();

void can_send(MESSAGE* msg);

void can_receive(MESSAGE* msg);
#endif