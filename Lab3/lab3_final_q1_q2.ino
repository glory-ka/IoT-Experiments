int bright_ratio = 0;	// brightness
int pinBrightness = 0;  // brightness of each pin
int fade = 0;	//how faded led is

int backup_bright_ratio;
int pinIdx;

int inputPOT; //Potentiometer voltage input on A0
int analogInPin = A0;
int value;	//value from potentiometer

int leds[] = {3,5,6,9,10,11};
int numLED = sizeof(leds)/sizeof(int); //dynamically determine the numbers of LEDs

int offset; // left-right LEDs or right-left LEDs

//turn off all the LEDs
void reset()
{
	//initial brightness		
	for(int ledPin = 0; ledPin < numLED; ledPin ++){
		analogWrite(leds[ledPin], LOW);
	}
  
}

void setup(){
	
	reset(); //initialize LEDs
	
  	//safe ratio in case bright_ration = 0;
	//that is because we don't use float, round to int. 0.9 -> 0
	backup_bright_ratio = map(102, 0, 1023, 0 , 255); // 102 is 10% of 1023
	
  
	// very important: set pinIdx to zero
	pinIdx = 0;
	offset = - 1; 
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
	
 
	// Each led is brighter than the privious one, except the last led
	pinBrightness = (bright_ratio ? bright_ratio : backup_bright_ratio) * ((offset < 0) ? pinIdx : numLED - pinIdx - 1);
	
	// update pin brightness| current_pin = ledPin - offset
	analogWrite(leds[pinIdx], pinBrightness);
	
	// move to next pin
	pinIdx = pinIdx - offset;

	delay(500);
	
	// if pinIdx = over max leds index || over min leds index
	if (pinIdx == numLED || pinIdx < 0)
	{
		offset = - offset; // reverse offset polarity
		pinIdx = (pinIdx < 0) ? pinIdx + 1 : pinIdx - 1;  // set pinIdx to max leds index or 0
		reset();
		
		delay(500);
	}
}