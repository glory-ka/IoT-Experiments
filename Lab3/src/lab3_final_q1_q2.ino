int bright_ratio = 0;	// brightness
int bright = 0;  // brightness of each pin
int fade = 0;	//how faded led is

int pinIdx;

int inputPOT; //Potentiometer voltage input on A0
int analogInPin = A0;
int value;	//value from potentiometer

int leds[] = {3,5,6,9,10,11};
int numLED = sizeof(leds)/sizeof(int); //dynamically determine the numbers of LEDs


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
  	Serial.begin(9600);
	
	// we go from -numLED to +numLED
	pinIdx = - numLED;
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
	// pinIdx -1 --> since we skipped zero below, and don't reach numLED. 
	// we could have used another variable, but ....
	bright = bright_ratio * ((pinIdx > 0) ? pinIdx -1 : -abs(pinIdx) + numLED); // part 1
	bright = (bright == 0) ? bright : fade + bright; //part 2
	
  	Serial.print(-abs(pinIdx) + numLED);
  	Serial.print("   ");
  	Serial.println(bright);
       
	
	// update pin brightness| current_pin = ledPin - offset
	analogWrite(leds[-abs(pinIdx) + numLED], bright);
	
	//move to next value to find next pin
	pinIdx ++; 

	delay(500);
	
	// if pinIdx==0 or numLED + 1--> change direction
	if (pinIdx == 0 || pinIdx == numLED + 1)
	{
		//skip zero, as [-abs(0) -numLED] --> (idx out of bound)
		// else reset to initial value
		pinIdx = (pinIdx == 0) ? 1 : -numLED;
		reset();
		
		delay(500); 
	}
}