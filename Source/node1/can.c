#include "can.h"
#include "mcp2515.h"

void can_init()
{
	mcp2515_init();
	
	/* Clear interrupt flag */
	mcp2515_bit_modify(0, 0b00000001, MCP_CANINTF);

	mcp2515_bit_modify(0x60, 0b01100000, MCP_RXB0CTRL); //receive buffer 0 control 
}


void can_send(MESSAGE* msg)
{
	mcp2515_write(MCP_TXB0SIDH, msg->id >> 3);
	mcp2515_write(MCP_TXB0SIDL, msg->id << 5);
	mcp2515_write(MCP_TXB0DLC, msg-> length);
	
	for (int length=0; length < msg->length; length++)
	{
		mcp2515_write(MCP_TXB0D0 + length, msg->data[length]);	
	}
	
	mcp2515_request_to_send(0);
}

void can_receive(MESSAGE* msg)
{
	if(mcp2515_read(MCP_CANINTF) & 0x01)
	{
		msg->length = mcp2515_read(MCP_RXB0DLC);
		msg->id = ((mcp2515_read(MCP_RXB0SIDH) << 3) + (mcp2515_read(MCP_RXB0SIDL) >> 5));
		for (int length=0; length < msg->length; length++)
		{
			msg->data[length] = mcp2515_read(MCP_RXB0D0 + length);
		}
	}
	mcp2515_bit_modify(0, 0b00000001, MCP_CANINTF);
}