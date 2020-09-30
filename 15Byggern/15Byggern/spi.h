#include <stdio.h>

void spi_init();
uint8_t spi_transmit(uint8_t data);

void spi_select_slave();
void spi_deselect_slave();