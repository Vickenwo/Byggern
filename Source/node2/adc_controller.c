#include "adc_controller.h"
#include "sam.h"
#include "game.h"

int registered = 0;

void adc_init()
{
	// disables Write Protect
	PMC->PMC_WPMR &=~(1<<0);
	
	//PMC->PMC_WPMR |= PMC_WPMR_WPKEY_Msk(0x504d43);
	
	//enable adc controller
	PMC->PMC_PCER1 |= PMC_PCER1_PID37; 
	
	//Enable freerun mode
	ADC->ADC_MR |= ADC_MR_FREERUN_ON;
	
	ADC->ADC_MR |= ADC_MR_PRESCAL(49);
	
	// track time
	ADC->ADC_MR |= 	ADC_MR_TRACKTIM(2) | ADC_MR_TRANSFER(0);

	//Begin Analog-to-digital conversion
	ADC->ADC_CR = ADC_CR_START; 
	
	//Enable channel 7, pin0 on arduino
	ADC->ADC_CHER = ADC_CHER_CH7;
	
	//Converted data is saved here until a new data conversion is completed. Only loaded if corresponding register is enabled
	ADC->ADC_CDR;
}

void adc_count_lives()
{
	if(ADC->ADC_CDR[7] < 0x2FF)
	{
		if(registered == 0)
		{
			game_decrease_lives();
			registered = 1;
		}
	}
	else
	{
		registered = 0;
	}
}