#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

#include "Game.h"
#include "Communicator.h"
#include "Timer.h"


Communicator* g_Communicator;
Game* g_Game;
Timer* g_Timer;

void setup() 
{
	g_Timer = new Timer;
	g_Game = new Game(g_Timer);
	g_Communicator = new Communicator(g_Game);
	g_Game->setCommunicator(g_Communicator);

	LittleFS.begin();

	Serial.begin(9600); 
	while (!Serial)
		continue;
	
}

void loop() 
{
	g_Communicator->handleSerialData();
	g_Timer->update();
}

