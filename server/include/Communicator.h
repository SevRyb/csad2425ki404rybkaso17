#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <Arduino.h>
#include <ArduinoJson.h>

#include "Data.h"
#include "Game.h"

class Game;
/**
 * @class Game
 * @brief The Communicator class responsible for handling communication with the game client
 */
class Communicator
{
public:
    /**
     * @brief Constructs a Communicator object with the provided Game instance
     * @param game The Game instance to be used by the Communicator
     */
    Communicator(Game* game);

    /**
     * @brief Notifies the game client that a new game has started
     * @param mode The play mode of the new game
     */
    void notifyGameStarted(PlayMode mode);
    /**
     * @brief Notifies the game client about a player's choice of a cell
     * @param cellId The identifier of the chosen cell
     * @param state The state of the chosen cell ('x', 'o', or ' ')
     */
    void notifyPlayerChoice(int cellId, char state);
    /**
     * @brief Notifies the game client that the game is over
     * @param winner The index of the winning player (0 for 'x', 1 for 'o', 2 for draw)
     */
    void notifyGameOver(int winner);
    /**
     * @brief Notifies the game client that the game has been loaded
     * @param cells The saved game state
     */
    void notifyGameLoaded(char cells[9]);

    /**
     * @brief Sends a JSON document to the game client
     * @param jsonDoc The JSON document to be sent
     */
    void sendJson(const JsonDocument& jsonDoc);
    /**
     * @brief Processes the incoming JSON data
     */
    void processJson();
    /**
     * @brief Handles the incoming serial data
     */
    void handleSerialData();

private:
    void onTestConnection(int magickNumber);

    Game* m_game;
    JsonDocument incomingJsonDoc;
};

//typedef Communicator g_Communicator;

#endif //COMMUNICATOR_H