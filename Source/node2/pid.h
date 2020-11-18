#ifndef PID_H
#define PID_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int lastProcessValue;
	int sumError;
	int prevError;
	float P_fac;
	int I_fac;
	int D_fac;
	int dt;
	int maxError;
	int maxSumError;
	
} PID_DATA;
	
PID_DATA pid;
void pid_init();

void pid_controller();
#endif