#ifndef MUSIC_H
#define MUSIC_H

//#include <stdio.h>
//#include <util/delay.h>
//#include <avr/io.h>
//#include <avr/interrupt.h>

//int caramelldansen_bpm;
//int caramelldansen_notes[];
//int caramelldansen_note_types[];
//int caramelldansen_length;

//int takeonme_length;
//int takeonme_note_types[];
//int takeonme[];
//int takeonme_bpm;

int hctb_length;
int hctb_note_types[];
int hctb[];
int hctb_bpm;

void music_PWM_init();

void music_play();

void music_play_note(int pitch, int length);

void music_play_song(int song);
#endif