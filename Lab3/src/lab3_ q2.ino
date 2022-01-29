int bright_ratio = 0;	// brightness
int pinBrightness = 0;  // brightness of each pin
int fade = 0;	//how faded led is

int backup_bright_ratio; // just in case bright_ratio is zero
int ledPin;

int inputPOT; //Potentiometer voltage input on A0
int analogInPin = A0;
int value;	//value from potentiometer

int leds[] = {3,5,6,9,10,11};
int numLED = sizeof(leds)/sizeof(int); //dynamically determine the numbers of LEDs

void reset()
{
	//initial brightness		
	for(int ledPin = 0; ledPin < numLED; ledPin ++){
		analogWrite(leds[ledPin], LOW);
	}
  
}

void setup(){
	
	reset();
	
  	//safe ratio in case bright_ration = 0;
	//that is because we don't use float only int. 0.9 -> 0
	backup_bright_ratio = map(102, 0, 1023, 0 , 255); // 102 is 10% of 1023
	
  
	// very important: reset ledPin to zero
	ledPin = 0;
}

void loop()
{
	//check current potentiometer value
	value = analogRead(analogInPin);

	//map fade to potentiometer
	fade = map(value, 0, 1023, 0, 255);
	
	//(floor - maxValue)/number_of_LEDs
	// numLED -1 --> because 1 led is off
	bright_ratio = (255 - fade)/(numLED -1);
	
 
	// each led is brighter than the privious one, except the first led
	pinBrightness = (bright_ratio ? bright_ratio : backup_bright_ratio) * ledPin;
	
	// update pin brightness
	analogWrite(leds[ledPin], pinBrightness);
	
	// move to next pin
	ledPin ++;

	delay(500);
	
	if (ledPin == numLED)
	{
		ledPin = 0;
		reset();
	}
}