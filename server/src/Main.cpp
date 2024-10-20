#include <Arduino.h>
#include <ArduinoJson.h>

#include "Communicator.h"


Communicator* g_Communicator;


void setup()
{
	g_Communicator = new Communicator;

	Serial.begin(9600); 
	while (!Serial)
		continue;
}

void loop()
{
	g_Communicator->handleSerialData();
}
