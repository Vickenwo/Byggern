#include "motor.h"
#include "joystick.h"
#include "sam.h"
#include "timer.h"



void encoder_set_min(int value)
{
	enc.min = value;
}

void encoder_set_max(int value)
{
	enc.max = value;
}

int encoder_get_min()
{
	return enc.min;
}

int encoder_get_max()
{
	return enc.max;
}

int encoder_get_pos()
{
	return enc.pos;
}

int encoder_get_offset()
{
	return enc.offset;
}

int encoder_get_range()
{
	return enc.range;
}


void motor_init()
{
	// disables Write Protect
	PMC->PMC_WPMR &=~(1<<0);
	
	PMC->PMC_PCER0 |= PMC_PCER0_PID13;
	//PMC->PMC_PCER0 |= PMC_PCER0_PID14;
	
	//Enable PIO register DIR pin32=PD10
	PIOD->PIO_PER |= PIO_PER_P10;
	PIOD->PIO_OER |= PIO_OER_P10;
	
	//Enable PIO register EN pin30=PD9
	PIOD->PIO_PER |= PIO_PER_P9;
	PIOD->PIO_OER |= PIO_OER_P9;
	
	//Clear Direction register. 
	PIOD->PIO_CODR |= PIO_CODR_P9;
	
	//Set Enable register
	PIOD->PIO_SODR |= PIO_SODR_P9;
	
	
	//Enable pins for reading encoder D70-DO0
	PIOD->PIO_PER |= PIO_PER_P8;
	PIOD->PIO_PER |= PIO_PER_P7;
	PIOD->PIO_PER |= PIO_PER_P6;
	PIOD->PIO_PER |= PIO_PER_P5;
	PIOD->PIO_PER |= PIO_PER_P4;
	PIOD->PIO_PER |= PIO_PER_P3;
	PIOD->PIO_PER |= PIO_PER_P2;
	PIOD->PIO_PER |= PIO_PER_P1;
	
	//Enable solenoid pin, pin50
	PIOC->PIO_PER |= PIO_PER_P13;
	PIOC->PIO_OER |= PIO_OER_P13;
	PIOC->PIO_SODR |= PIO_SODR_P13;
}

uint16_t motor_read_encoder()
{
	//enable output registers not OE. pin25=P0
	PIOD->PIO_PER |= PIO_PER_P0;
	PIOD->PIO_OER |= PIO_OER_P0;
	
	//Enable (output) register SEL. pin27=P2
	PIOD->PIO_PER |= PIO_PER_P2;
	PIOD->PIO_OER |= PIO_OER_P2;
	
	//Enable (Output) register not RST. pin26=P1
	PIOD->PIO_PER |= PIO_PER_P1;
	PIOD->PIO_OER |= PIO_OER_P1;
	
	//Set OE low to enable output of encoder
	PIOD->PIO_CODR |= PIO_CODR_P0;
	
	//Set SEL low to get the high byte
	PIOD->PIO_CODR |= PIO_CODR_P2;
	
	
	//10 microseconds delay
	for (int i=0; i<3200; i++){}
	
	//Write MSB. 
	uint8_t MSB = (PIOC->PIO_PDSR>>1) & (0xff) ;
	
	//Set SEL high to read low byte
	PIOD->PIO_SODR |= PIO_SODR_P2;
	
	//10 microseconds delay
	for (int i=0; i<3200; i++){}
	
	uint8_t LSB = (PIOC->PIO_PDSR>>1) & (0xff);
	
	//Reset low, active
	PIOD->PIO_CODR |= PIO_CODR_P1;
	//Reset high
	PIOD->PIO_SODR |= PIO_SODR_P1;
	
	//Set OE high to disable output of encoder
	PIOD->PIO_SODR |= PIO_SODR_P0;
	
	uint16_t encoder = (MSB <<8) & 0xff00 | (LSB);
	
	return encoder;
}

void motor_drive(float speed)
{
	if (speed<0)
	{
		motor_set_direction(1);
	}
	else
	{
		motor_set_direction(0);
	}
	DACC->DACC_CDR = abs(speed);
}

void motor_speed()
{
	int x_pos = joystick_get_x_pos();
	int threshold = 5;
	uint16_t speed = 0x1FF+abs(x_pos)*10;
	if (x_pos>threshold)
	{
		//DIR = 1 is right
		motor_set_direction(1);
	}
	else if (x_pos<-threshold)
	{
		//DIR = 0 is left
		motor_set_direction(0);
	}
	else
	{
		speed = 0;
	}
	//send motor speed
	DACC->DACC_CDR = speed;
}

void motor_speed_slider()
{
	int x_pos = slider_get_right();
	int threshold = 50;
	uint16_t speed = 0x1FF+abs(50-x_pos)*10;
	if (x_pos>threshold)
	{
		//DIR = 1 is right
		motor_set_direction(1);
	}
	else if (x_pos<threshold)
	{
		//DIR = 0 is left
		motor_set_direction(0);
	}
	else
	{
		speed = 0;
	}
	//send motor speed
	DACC->DACC_CDR = speed;
}


void motor_calibrate()
{
	int encoder = motor_read_encoder();
	
	int threshold = 0;
	int encoder_prev = encoder+threshold+1;
	
	motor_set_direction(1);
	DACC->DACC_CDR = 3000;
	
	while(abs(encoder-encoder_prev)>threshold)
	{
		printf("CALIBRATING1\n\n\n\n\n\n\n\n\n\r");
		encoder_prev = encoder;
		encoder = motor_read_encoder();
	}
	
	encoder_set_min(encoder);
	
	
	encoder_prev = encoder+threshold+1;
	
	motor_set_direction(0);
	
	while(abs(encoder-encoder_prev)>threshold)
	{
		printf("CALIBRATING2\n\n\n\n\n\n\n\n\n\r");
		encoder_prev = encoder;
		encoder = motor_read_encoder();
	}
	
	encoder_set_max(encoder);
	
	encoder_calculate_range();
	encoder_update_offset();
}

void encoder_update_offset()
{
	int offset;
	if(enc.min > enc.max)
	{
		offset = enc.min-ENCODER_MAX;
	}
	enc.offset = 0-offset;
}

int encoder_calculate(int value)
{
	if(value > enc.max+500)
	{
		value = value - ENCODER_MAX;
	}
	
	value = value + enc.offset;
	if(value < 0)
	{
		value = 0;
	}
	return value;
}

void encoder_calculate_range()
{
	int full_range = ENCODER_MAX - enc.min + enc.max;
	enc.range = full_range/100;
}

int encoder_calculated_read()
{
	int value = motor_read_encoder();
	
	value = encoder_calculate(value);
	
	enc.pos = value;
	
	return value;
}

void motor_set_direction(uint8_t value)
{
	enc.dir = value;
	if(value)
	{
		PIOD->PIO_SODR |= PIO_SODR_P10;
	}
	else
	{
		PIOD->PIO_CODR |= PIO_CODR_P10;
	}
}

uint8_t motor_get_direction()
{
	return enc.dir;
}


void motor_solenoid_shoot()
{
	if (joystick_get_btn()){
		PIOC->PIO_CODR = PIO_CODR_P13;
		counter_10_finished = 0;
		counter_10 = 0;
		joystick_set_btn(0);
	}
}
