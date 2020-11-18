#ifndef TIMER_H
#define TIMER_H


#include <stdio.h>
#define MID_VALUE 63000
#define UPPER_LIMIT 88200
#define LOWER_LIMIT 37800
#define THRESHOLD 1260

void timer_init();
void timer_set_duty_cycle(int duty_cycle);
int timer_calculate_duty_cycle(int value);

uint8_t counter_50;
uint8_t counter_50_finished;

uint8_t counter_10;
uint8_t counter_10_finished;

uint8_t timer_counter_50_finished();
void timer_counter_50_reset();
#endif