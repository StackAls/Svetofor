/*

*/

const int GREEN_LIGHT           = 9; 	// Green light time in seconds
const int AMBER_LIGHT           = 2;  	// Amber light time in seconds
const int RED_LIGHT           	= 9;	// Red light time in seconds
const int DEAD_LIGHT            = 4;  	// Dead light time in seconds

//Outputs:
int green   = 6;    // Green light output
int amber   = 5;    // Amber light output
int red     = 4;    // Red light output
int inmode	= 8;
volatile int mode	= 0;	//Mode
int state = 0;
int i = 0;

void setup() 
{
  // initialize // Serial:
  // Serial.begin(9600);
  // Set appropriate pin light outputs for Busy Bunny Lane
	pinMode(green, OUTPUT);
	pinMode(amber, OUTPUT);
	pinMode(red, OUTPUT);
	pinMode(inmode, INPUT);
  // Set initial states
  digitalWrite(green,LOW);
  digitalWrite(amber,LOW);
  digitalWrite(red,LOW);
  
  attachInterrupt(0, ChangeMode, RISING);
}

//===============================================================================
//  Main
//===============================================================================
void loop() 
{
	switch(mode)
	{
		case 0:
			AutoLight();
			break;
		case 1:
			ManualLight();
			break;
		case 2:
			BlinkLight();
			break;	
	}
}
void ManualLight()
{
	//// Serial.println("manual");
	state=digitalRead(inmode);
	if(state == HIGH)
	{
		// Serial.println("change state");
		delay(500);
		// Serial.print("i=");
		// Serial.println(i);
		if (i==1)
		{
			//amber green
			// Serial.println("red");
			digitalWrite(red,LOW);
			for (int seconds = 0; seconds <= DEAD_LIGHT; seconds++)
			{		
				delay(500);
				digitalWrite(green,HIGH);
				// Serial.println("G");
				delay(500);
				digitalWrite(green,LOW);
			}
			//amber
			digitalWrite(amber,HIGH);
			// Serial.println("A");
			delay(AMBER_LIGHT*1000);
			digitalWrite(amber,LOW);
			//red
			digitalWrite(red,HIGH);
			// Serial.println("R");
			i=0;
		}
		else
		{
			// Serial.println("green");
			digitalWrite(green,LOW);
			digitalWrite(red,HIGH);
			digitalWrite(amber,HIGH);
			// Serial.println("RA");
			delay(DEAD_LIGHT*1000/2);
			digitalWrite(red,LOW);
			digitalWrite(amber,LOW);
			digitalWrite(green,HIGH);
			// Serial.println("G");
			i=1;
		}
	}
}

void ChangeMode()
{
	if(mode < 2)
	{
		mode++;
	}
	else
	{
		mode=0;
	}
	digitalWrite(amber,HIGH);
	delay(800);
	digitalWrite(amber,LOW);

	// Serial.print("chan mode=");
	// Serial.println(mode);
}

void BlinkLight() 
{
//	// Serial.println("blink");
//green red off
    digitalWrite(green,LOW);
	digitalWrite(red,LOW);
//amber blink
	delay(500);
	digitalWrite(amber,HIGH);
	// Serial.println("A");
	delay(500);
	digitalWrite(amber,LOW);
}

void AutoLight() 
{
//	// Serial.println("auto");
//amber red
	digitalWrite(red,HIGH);
	digitalWrite(amber,HIGH);
	// Serial.println("RA");
	delay(DEAD_LIGHT*1000/2);
	digitalWrite(amber,LOW);
//green
	digitalWrite(red,LOW);
	digitalWrite(green,HIGH);
	// Serial.println("G");
	delay(GREEN_LIGHT*1000);
//blink green
	for (int seconds = 0; seconds <= DEAD_LIGHT; seconds++)
	{
		delay(500);
		digitalWrite(green,LOW);
		delay(500);
		digitalWrite(green,HIGH);
		// Serial.println("G");
	}
	digitalWrite(green,LOW);
//amber
	digitalWrite(amber,HIGH);
	// Serial.println("A");
	delay(AMBER_LIGHT*1000);
	digitalWrite(amber,LOW);
//red
	digitalWrite(red,HIGH);
	// Serial.println("R");
	delay(RED_LIGHT*1000);	
}

