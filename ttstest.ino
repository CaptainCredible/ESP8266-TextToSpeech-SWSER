#include <Arduino.h>
#include <ESP8266SAM.h>
#include <AudioOutputI2SNoDAC.h>
#include <SoftwareSerial.h>
#define BAUD_RATE 115200
#define buffSize 512
#include <ESP8266WiFi.h>
SoftwareSerial swSer(14, 12, false, buffSize); // rx,tx,inverse_logic, buffsize 
AudioOutputI2SNoDAC  *out = NULL;


void setup()
{
	out = new AudioOutputI2SNoDAC();
	out->begin();

	talk("Welcome to the microbit orchestra!");

	swSer.begin(BAUD_RATE);
	swSer.println("\nSoftware serial test started");
	WiFi.mode(WIFI_OFF);
	WiFi.forceSleepBegin();
}

void loop()
{
	if (swSer.available()) {
		char buf[buffSize]; //make an array of 512 char
		int len; //variable for length of buffer
		len = swSer.readBytesUntil('\n',buf, buffSize-1);
		buf[len] = '\0'; //put null terminator at the end
		talk(buf);
	}
}

bool singFlip = false;
int throatInc = 0;

void talk(char* what) {

	ESP8266SAM *sam = new ESP8266SAM;
	sam->SetSingMode(singFlip);
	//sam->SetThroat(throatInc);
	//sam->SetSpeed(100);
	sam->Say(out, what);

	singFlip = !singFlip;
	throatInc = (throatInc + 1) % 10;
	
	delete sam;
}


