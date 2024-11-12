#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

#include "Game.h"
#include "Communicator.h"
#include "Timer.h"

/**
 * @brief The global instance of the Communicator class
 */
Communicator* g_Communicator;
/**
 * @brief The global instance of the Game class
 */
Game* g_Game;
/**
 * @brief The global instance of the Timer class
 */
Timer* g_Timer;

/**
 * @brief The setup function, which is called once at the start of the program
 */
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

/**
 * @brief The main loop function, which is called repeatedly
 */
void loop() 
{
	g_Communicator->handleSerialData();
	g_Timer->update();
}

