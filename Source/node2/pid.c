#include "pid.h"
#include "sam.h"
#include "joystick.h"
#include "motor.h"
#include "timer.h"

static Tc *tc = 0x40080000;

void pid_timer_init()
{
	//Peripheral clock enable
	PMC->PMC_PCER0 |= PMC_PCER0_PID27;
	PIOB->PIO_PDR |= PIO_PDR_P25;
	PIOB->PIO_ABSR |= PIO_ABSR_P25;
}

void pid_init() 
{
	pid.sumError = 0;
	pid.lastProcessValue = 0;
	pid.prevError = 0;
	pid.P_fac = 50;
	pid.I_fac = 7;
	pid.D_fac = 2;
	pid.dt = 1/50;	
}

void pid_controller()
{
	int error=0;
	int u;
	int encoder = encoder_get_pos()/encoder_get_range();
	error = 100 - slider_get_right() - encoder;
	
	if(counter_50_finished)
	{
		pid.sumError+=pid.dt*error;
		printf("SUM ERROR %d\n\r", pid.sumError);
		printf("50 reached\n\r");
		counter_50_finished = 0;
	}
	
	u = (int)(pid.P_fac*error+ pid.dt*pid.I_fac*pid.sumError+(pid.D_fac/pid.dt)*(error- pid.prevError));
	printf("Encoder: %d, Slider: %d, E: %d, U: %d\n\r", 100-encoder, slider_get_right(), (int)error, u);
	if(u>3000)
	{
		u=3000;
	}
	else if (u<-3000)
	{
		u=-3000;
	}
	pid.prevError = error;	
	motor_drive(u);
}