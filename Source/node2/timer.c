#include "timer.h"
#include "sam.h"
#include "game.h"

int duty_cycle = MID_VALUE;

void timer_init() 
{
	// disables Write Protect
	PMC->PMC_WPMR &=~(1<<0);
	
	//Enables the corresponding peripheral clock (timer counter channel 0)
	PMC->PMC_PCER0 |= (1<<27);
	
	//Enables the clock if CLKDIS is not 1
	TC0->TC_CHANNEL[0].TC_CCR |= TC_CCR_CLKEN;
	
	//clear CLKDIS 
	TC0->TC_CHANNEL[0].TC_CCR &= ~(TC_CCR_CLKDIS);
	
	//Software trigger:the counter is reset and the clock is started
	TC0->TC_CHANNEL[0].TC_CCR |= TC_CCR_SWTRG;
	
	//Set Wave-bit to 1 (to enable read/write in TC registers)
	TC0->TC_CHANNEL[0].TC_CMR |= TC_CMR_WAVE;
	
	//UP mode with automatic trigger on RC compare
	TC0->TC_CHANNEL[0].TC_CMR |= TC_CMR_WAVSEL_UP_RC;
	
	//Clearing RA compare effect on TIOA
	TC0->TC_CHANNEL[0].TC_CMR |= TC_CMR_ACPA_CLEAR;
	
	//Set RC compare effect on TIOA
	TC0->TC_CHANNEL[0].TC_CMR |= TC_CMR_ACPC_SET;
	
	//PIOB beacuse PWM2 = PB25. Disables the PIO from controlling P25
	PIOB->PIO_PDR |= PIO_PDR_P25;
	
	//selecting peripheral B
	PIOB->PIO_ABSR |= PIO_ABSR_P25;
	
	TC0->TC_CHANNEL[0].TC_RA = 63000; //duty cycle
	TC0->TC_CHANNEL[0].TC_RC = 840000; //period
	
	// interrupt on rc compare
	TC0->TC_CHANNEL[0].TC_IER |= TC_IER_CPCS;
	
	// enable interrupt
	TC0->TC_CHANNEL[0].TC_CMR |= TC_CMR_AEEVT_SET;
	NVIC_EnableIRQ(ID_TC0);
	
	counter_10 = 0;
	counter_10_finished = 1;
	counter_50 = 0;
	counter_50_finished = 0;
}

void TC0_Handler()
{
	char tc_sr = TC0->TC_CHANNEL[0].TC_SR;
	if(tc_sr)
	{
		if(!counter_10_finished)
		{
			counter_10 += 1;
			if(counter_10 >= 10)
			{
				counter_10_finished = 1;
				PIOC->PIO_SODR = PIO_SODR_P13;
			}
		}
		counter_50 += 1;
		if(counter_50 >= 50)
		{
			game_increase_score();
			counter_50_finished = 1;
			counter_50 = 0;
		}
	}
	NVIC_ClearPendingIRQ(ID_TC0);
}


int timer_calculate_duty_cycle(int value)
{
	return (int)(((float)(value+100)*(1.2/200)+0.9)/20*840000);
}


void timer_set_duty_cycle(int value)
{
	if(value > MID_VALUE-THRESHOLD && value < MID_VALUE+THRESHOLD){value = MID_VALUE;}
	if(value > UPPER_LIMIT){value = UPPER_LIMIT;}
	if(value < LOWER_LIMIT){value = LOWER_LIMIT;}
	TC0->TC_CHANNEL[0].TC_RA = value;
}


uint8_t timer_counter_50_finished()
{
	if(counter_50>=50)
	{
		return 1;
	}
	return 0;
}

void timer_counter_50_reset()
{
	counter_50 = 0;
}