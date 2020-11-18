/*
 * interrupt.c
 *
 * Author: Gustav O. Often and Eivind H. J�lsgard
 *
 * For use in TTK4155 Embedded and Industrial Computer Systems Design
 * NTNU - Norwegian University of Science and Technology
 *
 */ 

#include "can_interrupt.h"

#include <stdio.h>
#include "sam.h"

#include "printf-stdarg.h"

#include "can_controller.h"

#include "joystick.h"
#include "timer.h"
#include "motor.h"
#include "game.h"

#define DEBUG_INTERRUPT 1

void CAN0_Handler( void )
{
	printf("INTERRUPT HANDLER\n\r");
	
	if(DEBUG_INTERRUPT)printf("CAN0 interrupt\n\r");
	char can_sr = CAN0->CAN_SR; 
	
	//RX interrupt
	if(can_sr & (CAN_SR_MB1 | CAN_SR_MB2) )//Only mailbox 1 and 2 specified for receiving
	{
		CAN_MESSAGE message;
		if(can_sr & CAN_SR_MB1)  //Mailbox 1 event
		{
			can_receive(&message, 1);

		}
		else if(can_sr & CAN_SR_MB2) //Mailbox 2 event
		
		{
			can_receive(&message, 2);
		}
		else
		{
			printf("CAN0 message arrived in non-used mailbox\n\r");
		}
		
		switch(message.id)
		{
			case JOYSTICK_ID:
				joystick_update(message.data[0], message.data[1], message.data[2]);
				timer_set_duty_cycle(timer_calculate_duty_cycle(joystick_get_x_pos()));
				break;
				
			case SLIDER_ID:
				slider_update(message.data[0], message.data[1]);
				printf("Left button: %d\n\r", message.data[2]);
				if (message.data[2])
				{
					printf("EXITING GAME");
					game_exit();
				}
				break;
			case CALIBRATE_ID:
				motor_calibrate();
				break;
			case GAME_STATE_ID:
				switch(message.data[0])
				{
					case INIT:
						game_init();
						break;
					case RESTART:
						game_restart();
						break;
						
					default:
						break;
				}
		}
	}
	
	if(can_sr & CAN_SR_MB0)
	{
		if(DEBUG_INTERRUPT) printf("CAN0 MB0 ready to send \n\r");
		
	//Disable interrupt
		CAN0->CAN_IDR = CAN_IER_MB0;
	}

	if(can_sr & CAN_SR_ERRP)
	{
		if(DEBUG_INTERRUPT)printf("CAN0 ERRP error\n\r");

	}
	if(can_sr & CAN_SR_TOVF)
	{
		if(DEBUG_INTERRUPT)printf("CAN0 timer overflow\n\r");

	}
	
	NVIC_ClearPendingIRQ(ID_CAN0);
}
