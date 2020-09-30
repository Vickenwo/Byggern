#include "can.h"
#include "mcp2515.h"

void can_init(){
	mcp2515_init();
	/* Set loop-back mode */
	mcp2515_write(MODE_LOOPBACK, MCP_CANCTRL);
}

void can_send(MESSAGE* msg){
	//mcp2515_write(MCP_, msg->ID << 5);
}

MESSAGE can_receive(){

}