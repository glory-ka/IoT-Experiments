// Team 3 Giovanni, Tonny, Farzaad, Glodi
// Application Developer: Giovanni
// Lab 1 Question 1

#include <Arduino.h>
#include <unity.h>


// leds 1 to 8 set to pins 2 to 9 respectively
uint8_t leds[] = {2, 3, 4, 5, 6, 7, 8, 9};

void test_led_state_high(void)
{
		
	for (uint8_t led=0; led < sizeof(leds); led ++)
	{
		digitalWrite(leds[led], HIGH);
		TEST_ASSERT_EQUAL(digitalRead(leds[led]), HIGH);
		delay(1000);
	}
}

void test_led_state_low(void)
{
		
	for (int8_t led=sizeof(leds)-1; led > 0; led --)
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
