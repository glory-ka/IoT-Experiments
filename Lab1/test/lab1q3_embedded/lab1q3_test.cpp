// Team 3 Giovanni, Tonny, Farzaad, Glodi
// Application Developer: Giovanni
// Lab 1 Question 3

#include <Arduino.h>
#include <unity.h>


#define LED_NUMBER 8

// leds 1 to 8 set to pins 2 to 9 respectively
uint8_t leds[LED_NUMBER] = {2, 3, 4, 5, 6, 7, 8, 9};

void test_led_state_high(void)
{
		
	for (uint8_t led=0; led < LED_NUMBER; led += 2)
	{
		digitalWrite(leds[led], HIGH);
		TEST_ASSERT_EQUAL(digitalRead(leds[led]), HIGH);
		delay(1000);
	}
}

void test_led_state_low(void)
{
		
	for (int8_t led=LED_NUMBER-2; led > 0; led -= 2)
	{
		digitalWrite(leds[led], LOW);
		TEST_ASSERT_EQUAL(digitalRead(leds[led]), LOW);
		delay(1000);
	}
}


void setup() {
}

void loop() {

	RUN_TEST(test_led_state_high);
	delay(1000);
	RUN_TEST(test_led_state_low);
	UNITY_END(); // stop unit testing
}
