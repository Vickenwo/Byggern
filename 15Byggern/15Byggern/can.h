#include <stdint.h>

typedef struct{
	uint8_t id, data, length;
}MESSAGE;

void can_init();

void can_send(MESSAGE* msg);

MESSAGE can_receive();