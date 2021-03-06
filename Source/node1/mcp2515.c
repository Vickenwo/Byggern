#include "mcp2515.h"

uint8_t mcp2515_read(uint8_t address)
{
	spi_select_slave();
	spi_transmit(MCP_READ);
	spi_transmit(address);
	uint8_t data = spi_transmit(0); //dummy byte
	spi_deselect_slave();
	return data;
}

void mcp2515_write(uint8_t address, uint8_t data)
{
	spi_select_slave();
	spi_transmit(MCP_WRITE);
	spi_transmit(address);
	spi_transmit(data);
	spi_deselect_slave();
}

void mcp2515_request_to_send(uint8_t pin_select)
{
	spi_select_slave();
	switch(pin_select) {
		case (0):
			spi_transmit(MCP_RTS_TX0);
			break;
		case (1):
			spi_transmit(MCP_RTS_TX1);
			break;
		case (2):
			spi_transmit(MCP_RTS_TX2);
			break;
		case (3):
			/* 3 = ALL */
			spi_transmit(MCP_RTS_ALL);
			break;
		default:
			break;
			
	}
	spi_deselect_slave();
	
}

void mcp2515_bit_modify(uint8_t data, uint8_t mask, uint8_t address)
{
	spi_select_slave();
	spi_transmit(MCP_BITMOD);
	spi_transmit(address);
	spi_transmit(mask);
	spi_transmit(data);
	spi_deselect_slave();
}

void mcp2515_reset()
{
	spi_select_slave();
	spi_transmit(MCP_RESET);
	spi_deselect_slave();
	mcp2515_bit_modify(0x80, 0xe0, MCP_CANCTRL);
}

uint8_t mcp2515_read_status()
{
	return mcp2515_read(MCP_READ_STATUS);
}

void mcp2515_init()
{
	spi_init();
	mcp2515_reset();
	
	mcp2515_write(MCP_CNF3, 0x1);
	mcp2515_write(MCP_CNF2, 0xb5);
	mcp2515_write(MCP_CNF1, 0x43);
	
		/* Enable interrupt when received message*/
	mcp2515_bit_modify(MCP_RX_INT, 0b00000011, MCP_CANINTE);
		//mcp2515_bit_modify(0x60, MCP_RXB0CTRL, 0b01100000); //recieve buffer 0 control
	
	/* Set loop-back mode */
	mcp2515_bit_modify(MODE_NORMAL, MODE_MASK, MCP_CANCTRL);
	_delay_ms(100);
}