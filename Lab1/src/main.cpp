// Team 4 Giovanni, Tonny, Farzaad, Glodi
// Application Developer: Giovanni
// Lab 1 Question 1

#include <Arduino.h>

// leds 1 to 8 set to pins 2 to 9 respectively
#define LED_NUMBER 8


uint8_t leds [LED_NUMBER] = {2, 3, 4, 5, 6, 7, 8, 9}; 

// initialize pins 2 to 9 for output
void setup() 
{

	for (uint8_t led=0; led < LED_NUMBER; led ++)
	{
		pinMode(leds[led], OUTPUT);
	}
}

// loop leds to turn on one by one then turn off one by one (question 1)
void loop() {

	//TURN ON ALL THE LEDS
	for (uint8_t led=0; led < LED_NUMBER; led ++)
	{
		digitalWrite(leds[led], HIGH);
		delay(1000);
	}

	// TURNS OFF ALL THE LEDS
	for (int8_t led=LED_NUMBER-1; led >= 0; led --)
	{
		digitalWrite(leds[led], LOW);
		delay(1000);
	}


	delay(3000);

	//TURN ON ALL THE ODD LEDS
	for (uint8_t led=1; led < LED_NUMBER; led +=2)
	{
		digitalWrite(leds[led], HIGH);
		delay(1000);
	}

	// TURNS OFF ALL THE ODD LEDS
	for (int8_t led=LED_NUMBER-1; led >= 0; led -= 2)
	{
		digitalWrite(leds[led], LOW);
		delay(1000);
	}

  delay(3000);

	//TURN ON ALL THE EVEN LEDS
	for (uint8_t led=0; led < LED_NUMBER; led += 2)
	{
		digitalWrite(leds[led], HIGH);
		delay(1000);
	}

	// TURNS OFF ALL THE EVEN LEDS
	for (int8_t led=LED_NUMBER-2; led >= 0; led -= 2)
	{
		digitalWrite(leds[led], LOW);
		delay(1000);
	}
}

