#include "dac.h"
#include "sam.h"

void dac_init()
{
	// disables Write Protect
	PMC->PMC_WPMR &=~(1<<0);
	
	//PMC->PMC_WPMR |= PMC_WPMR_WPKEY_Msk(0x504d43);
	
	//enable dac controller
	PMC->PMC_PCER1 |= PMC_PCER1_PID38; //Eventuelt PMC_PCER1_PID38
	
	//Disable trigger mode to Enable freerun mode
	DACC->DACC_MR |= DACC_MR_TRGEN_DIS;
	
	//Select channel 1
	DACC->DACC_MR |= DACC_MR_USER_SEL_CHANNEL1;
	
	//Enable channel 1, DAC1 on arduino
	DACC->DACC_CHER = DACC_CHER_CH1;
	
	//Initial speed value
	DACC->DACC_CDR = 0;
}