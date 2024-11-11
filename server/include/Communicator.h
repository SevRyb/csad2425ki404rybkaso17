#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <Arduino.h>
#include <ArduinoJson.h>

#include "Data.h"
#include "Game.h"

class Game;
class Communicator
{
public:
    Communicator(Game* game);

    void notifyGameStarted(PlayMode mode);
    void notifyPlayerChoice(int cellId, char state);
    void notifyGameOver(int winner);
    void notifyGameLoaded(char cells[9]);

    void sendJson(const JsonDocument& jsonDoc);
    void processJson();
    void handleSerialData();

private:
    void onTestConnection(int magickNumber);

    Game* m_game;
    JsonDocument incomingJsonDoc;
};

//typedef Communicator g_Communicator;

#endif //COMMUNICATOR_H