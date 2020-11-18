#ifndef MOTOR_H
#define MOTOR_H

#include <stdio.h>
#include <stdlib.h>
#define ENCODER_MAX 65535
#define ENCODER_MIN 0

typedef struct  
{
	int max, min, pos, offset, dir, range;
}Encoder;

Encoder enc;


void encoder_set_min(int value);

void encoder_set_max(int value);

int encoder_get_pos();

int encoder_get_min();

int encoder_get_max();

int encoder_get_offset();

int encoder_get_range();

void motor_set_direction(uint8_t value);

uint8_t motor_get_direction();

void motor_init();

uint16_t motor_read_encoder();

void motor_drive(float speed);

void motor_speed();

void motor_speed_slider();

void motor_calibrate();

void encoder_update_offset();

int encoder_calculate(int value);

int encoder_calculated_read();

void motor_solenoid_shoot();
#endif