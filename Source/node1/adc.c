#define F_CPU 4915200

#ifndef stdio.h
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"
#endif


#define ADC_REGISTER 0x1400


void PWM_init()
{
	DDRD |= (1<<PD5);
	
	// Timer/Counter Register for A. Set fast PWM WGM1=1110 Waveform mode. No prescaling clock
	TCCR1A = (0<<WGM10) | (1<<WGM11) | (1<<COM1A1) | (1<<COM1A0);
	TCCR1B = (1<<WGM12) | (1<<WGM13) | (1<<CS10) | (0<<CS11) | (0<<CS12);
	
	//Input Capture register. Define Counter TOP value, the period
	ICR1 = 10;
	//Output Compare. Define duty cycle 0.5*period
	OCR1A = 5;
	sei();
}

ISR (TIMER1_COMPA_vect){}

uint8_t adc_read(uint8_t ainx){
	volatile uint8_t *reg_adc = (uint8_t *) ADC_REGISTER;
	reg_adc[0] = 0x80 | ainx;
	_delay_ms(20);
	return reg_adc[0];
}
