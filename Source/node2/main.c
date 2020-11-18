/*
 * node2.c
 *
 * Created: 07.10.2020 16:54:01
 * Author : Mats  Mathisen, Jananni Johanraj & Victoria T. Kenworthy
 */ 

#define BAUD 9600
#include "sam.h"
#include "uart.h"
#include "can_controller.h"
#include "printf-stdarg.h"+
#include "can_interrupt.h"
#include "timer.h"
#include "joystick.h"
#include "adc_controller.h"
#include "dac.h"
#include "motor.h"
#include "pid.h"


void init()
{
	/* Initialize the SAM system */
	SystemInit();
	configure_uart();
	can_init_def_tx_rx_mb(0x290561); //set CAN_BR
	timer_init();
	adc_init();
	dac_init();
	joystick_init();
	slider_init();
	motor_init();
	timer_set_duty_cycle(63000);
	motor_calibrate();
	pid_init();

	//led_illuminate();
}


int main(void)
{
	init();
	while (1)
	{
		if(game_get_in_game())
		{
			pid_controller();
			encoder_calculated_read();
			motor_solenoid_shoot();
			adc_count_lives();
			
			if(game_get_lives() <= 0)
			{
				game_exit();
			}
		}
	}
}

void led_illuminate()
{
	PIOA->PIO_OER = 0x1u << 19;
	PIOA->PIO_SODR = PIO_SODR_P19;
	//PIOA->PIO_OER = 0x1u << 20;
	//PIOA->PIO_SODR = PIO_SODR_P20;
}