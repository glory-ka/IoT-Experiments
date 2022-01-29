#include <IRremote.h>

// Remote Controlled based sound melody player
//#include "pitches.h"
// Remote Controlled based sound melody player
/*************************************************
 * Public Constants 
 *************************************************/
//https://gist.github.com/mikeputnam/2820675
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

// declare function -> usually done in header.h file
void play_melody (int melody[], int noteDurations[]);

// notes in the melody
int melody1[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int melody2[] = {NOTE_F3, NOTE_G3, NOTE_C3, NOTE_A3, NOTE_F4, 0, NOTE_B3, NOTE_C4};
int melody3[] = {NOTE_F3, NOTE_G3, NOTE_C3, NOTE_D3, NOTE_F4, 0, NOTE_E3, NOTE_D4};
int melody4[] = {NOTE_F1, NOTE_G3, NOTE_C3, NOTE_B3, NOTE_F4, 0, NOTE_G3, NOTE_C4};
int melody5[] = {NOTE_F3, NOTE_G3, NOTE_C3, NOTE_A3, NOTE_F4, 0, NOTE_A3, NOTE_E4};

// note durations: 4 = quarter note, 8 = eighth note, etc.: 
int noteDurations1[] = {4, 8, 8, 4, 4, 4, 4, 4};
int noteDurations2[] = {8, 4, 8, 4, 8, 2, 4, 4};
int noteDurations3[] = {8, 4, 8, 4, 8, 2, 2, 4};
int noteDurations4[] = {8, 4, 2, 4, 8, 2, 16, 4};
int noteDurations5[] = {16, 2, 8, 4, 8, 4, 4, 4};

// buz pin
int tonePin = 7;

// infrared pin
int irPin = 8;

void setup()
{
	pinMode (irPin, INPUT);
	Serial.begin (9600);
	Serial.println ("Remote Controlled melody player");
	Serial.println ("Press a key from 1 to 5 to play a melody");
}

// Step 1: Read the duration (of pulses) of key pressed using micros()
// on the Remote Control and store in an array
// Step 2: Find out the exact key pressed based on the code

void loop()
{
	int bits_len = 24;
	unsigned int arr[ bits_len ];
	unsigned long val = 0;
	unsigned long startTime, endTime;
	
	// loop till any key on remote is not pressed
	// when key is pressed the value is LOW
	while (digitalRead (irPin) == HIGH);
	
	// loop to receive 24 bits of key press on remote control
	for (int i = 0; i < bits_len; i++)
	{
		// loop till a key is pressed
		while (digitalRead (irPin) == LOW);

		// once a key is pressed note the start time
		startTime = micros();
		
		// loop till key is released
		while (digitalRead (irPin) == HIGH);
		
		// after key is released note the end time
		endTime = micros();
		
		// store the difference in the time interval
		arr[ i ] = endTime - startTime;
	
	}
	
	for (int i = 0; i < bits_len; i++)
	{
		// if the time interval more than 1000 microseconds
		if (arr[ i ] > 1000)
		{
			// binary to decimal conversion
			// 1 << i is nothing but 2 raised to the power of i

			val = val + (1l << i);
		}
	}
	
	switch (val)
	{
		// Key 1, channel 1
		case 0x25FA03 :
			Serial.println ("Playing melody-1");
			play_melody (melody1, noteDurations1);
		break;
		
		// Key 2, channel 2
		case 0x27FA03 :
			Serial.println ("Playing melody-2");
			play_melody (melody2, noteDurations2);
		break;
		
		// Key 3, channel 3
		case 0x99FA03 :
			Serial.println ("Playing melody-3");
			play_melody (melody3, noteDurations3);
		break;
		
		// Key 4, channel 4
		case 0x1DFA03 :
			Serial.println ("Playing melody-4");
			play_melody (melody4, noteDurations4);
		break;
		
		// Key 5, channel 5
		case 0x1FFA03 :
			Serial.println ("Playing melody-5");
			play_melody (melody5, noteDurations5);
		break;
		
		case 0x91FA03 :
			Serial.println ("Key 6");
			delay (1000);
		break;
		
		case 0x15FA03 :
			Serial.println ("Key 7");
			delay (1000);
		break;
		
		case 0x17FA03 :
			Serial.println ("Key 8");
			delay (1000);
		break;
		
		case 0x89FA03 :
			Serial.println ("Key 9");
			delay (1000);
		break;
		
		default :
			Serial.println ("Press any key from 1 to 9");
	}
}

void play_melody (int melody[], int noteDurations[])
{
	for (int thisNote = 0; thisNote < 8; thisNote++)
	{
		// to calculate the note duration, take one second
		// divided by the note type
		// i.e. quarter note = 1000 / 4, eighth note = 1000 / 8, etc.
		int noteDuration = 1000 / noteDurations[ thisNote ];
		
		tone (tonePin, melody[ thisNote ], noteDuration);
		
		// to distinguish the notes, set a minimum time between them.
		// the note's duration + 30% work well:
		int pauseBetweenNotes = noteDuration * 1.30;
		
		delay (pauseBetweenNotes);
		
		// stop the tone playing
		noTone (tonePin);
	}
}
