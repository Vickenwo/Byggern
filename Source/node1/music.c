#include <avr/io.h>
#include <util/delay.h>
#include "music.h"
#include "pitches.h"
#include "joystick.h"

#define F_CPU 4915200

void music_PWM_init(){
	// Set Pin PD4 as output
	DDRD = (1<<4);
	
	//Waveform mode, Compare on top with prescaling clk/8
	TCCR3A = (1<<WGM31) | (1<<COM3A1);
	TCCR3B = (1<<WGM33) | (1<<WGM32) | (1<<CS31);// | (1 <<CS30);
	
	//music_play_note(NOTE_A6, 1000);
	//Set frequency
	//ICR3 = 880;
	////Set duty cycle
	//OCR3A = 440;
}

void music_play_note(int pitch, int length)
{
	int new_period = (int) (F_CPU/(2*8*pitch)) - 1;
	ICR3 = new_period;
	OCR3A = (int)(new_period/2);
	for(int i = 0; i < length; i++)
	{
		_delay_ms(2);
	}
}

void music_play()
{
	for(int current_note = 0; current_note < hctb_length; current_note++)
	{
		int note_length = hctb_note_types[current_note]*hctb_bpm;
		music_play_note(hctb[current_note], note_length);
		_delay_ms(100);
		
		music_play_note(0, 10);
		_delay_ms(10);
		
		if(BUTTON_PRESSED)
		{
			
			break;
		}
	}
	music_play_note(0,10);
}


//void music_play_song(int title)
//{
	//int clk_per_beat;
	//switch(title)
	//{
		//case 1:
		//clk_per_beat = caramelldansen_bpm;//42000000*60000/caramelldansen_bpm;
		//for(int current_note = 0; current_note < caramelldansen_length; current_note++)
		//{
			//int note_length = caramelldansen_note_types[current_note]*clk_per_beat;
			//
			//music_play_note(caramelldansen_notes[current_note], note_length);
			//
			//_delay_ms(100);
			//
			//music_play_note(0,10);
			//_delay_ms(10);
			//
		//}
		//break;
		//case 2:
			//clk_per_beat = takeonme_bpm;
			//for(int current_note = 0; current_note < takeonme_length; current_note++)
			//{
				//
			//
				//int note_length = takeonme_note_types[current_note]*clk_per_beat;
				//music_play_note(takeonme[current_note], note_length);
				//_delay_ms(100);
				//
				//music_play_note(0,10);
				//_delay_ms(10);
			//}
		//break;
		//case 3:
			//for(int current_note = 0; current_note < hctb_length; current_note++)
			//{
				//int note_length = hctb_note_types[current_note]*hctb_bpm;
				//music_play_note(hctb[current_note], note_length);
				//_delay_ms(100);
				//
				//music_play_note(0,10);
				//_delay_ms(10);
			//}
	//}
	//music_play_note(0,10);
//}


//// CARAMELLDANSEN
//int caramelldansen_bpm = 165;
//int caramelldansen_notes[] =
//{
	////verse
	//NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_FS5,
	//NOTE_GS5, NOTE_AS5, NOTE_AS5,
	//NOTE_CS6, NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_FS5,
	//NOTE_AS5, NOTE_GS5, NOTE_FS5,
	//NOTE_F5, NOTE_DS5, NOTE_CS5,
	//NOTE_CS5, NOTE_CS5, NOTE_CS5, NOTE_CS5, NOTE_CS5, NOTE_DS5, NOTE_F5,
	//NOTE_FS5, NOTE_DS5, NOTE_CS5,
	//NOTE_FS6, NOTE_DS6, NOTE_CS6,
	////chorus
	//NOTE_CS3, NOTE_AS3, NOTE_GS3, NOTE_FS3, NOTE_GS3,
	//NOTE_FS3, NOTE_GS3, NOTE_FS3, NOTE_GS3, NOTE_AS3,
	//NOTE_DS3, NOTE_AS3, NOTE_GS3, NOTE_FS3, NOTE_FS3, NOTE_GS3,
	//NOTE_FS3, NOTE_GS3, NOTE_AS3, NOTE_GS3, NOTE_FS3,
	//NOTE_CS3, NOTE_AS3, NOTE_GS3, NOTE_FS3, NOTE_GS3,
	//NOTE_FS3, NOTE_GS3, NOTE_FS3, NOTE_GS3, NOTE_AS3,
	//NOTE_CS4, NOTE_B3, NOTE_AS3, NOTE_FS3, NOTE_FS3, NOTE_GS3,
	//NOTE_GS3, NOTE_AS3, NOTE_GS3, NOTE_FS3
//};
//////types in amount of 16ths
//int caramelldansen_note_types[] =
//{
	////verse 36
	//2,2,2,2,4,2,2,
	//2,4,10,
	//2,2,2,2,4,2,2,
	//2,4,10,
	//4,2,12,
	//2,2,2,2,2,2,2,
	//4,2,10,
	//4,2,10,
	////chorus 41
	//4,2,2,6,4,
	//2,2,2,4,4,
	//4,2,2,4,2,4,
	//2,2,2,4,4,
	//4,2,2,6,4,
	//2,2,2,4,4,
	//4,2,2,4,2,4,
	//2,4,4,4
//};

//int caramelldansen_length = 77;


////TAKE ON ME
//int takeonme_bpm = 169;
//int takeonme[] =
//{NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5,
	//NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5,
	//NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5,
//NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5};
////types in amount of 16ths
//int takeonme_note_types[] =
//{
	//2, 2, 2, 4, 4, 4,
	//4, 2, 2, 2, 2, 2,
	//2, 2, 2, 4, 4, 4,
//4, 2, 2, 2, 2, 2};
//
//int takeonme_length = 24;



//HERE COMES THE BRIDE
//int hctb_bpm = 81;
int hctb_bpm = 270;
int hctb[] =
{
	NOTE_F3, NOTE_AS3, 0, NOTE_AS3, NOTE_AS3, 0,
	NOTE_F3, NOTE_C4, 0, NOTE_A3, NOTE_AS3, 0,
	NOTE_F3, NOTE_AS3, NOTE_DS4, NOTE_DS4, NOTE_D4, NOTE_C4,
	NOTE_AS3, NOTE_C4, NOTE_AS3, NOTE_A3, NOTE_AS3, NOTE_C4, 0,
	NOTE_F3, NOTE_AS3, 0, NOTE_AS3, NOTE_AS3, 0,
	NOTE_F3, NOTE_C4, 0, NOTE_A3, NOTE_AS3, 0,
	NOTE_F3, NOTE_AS3, NOTE_D4, NOTE_F4, NOTE_D4, NOTE_AS3,
	NOTE_G4, NOTE_F4, NOTE_DS4, NOTE_D4, NOTE_C4,
	NOTE_AS3
};

int hctb_note_types[] =
{
	4,2,1,1,4,4,
	4,2,1,1,4,4,
	4,3,1,4,3,1,
	2,1,1,3,1,4,4,
	4,2,1,1,4,4,
	4,2,1,1,4,4,
	4,3,1,4,3,1,
	8,2,2,3,1,
	16
};

int hctb_length = 49;