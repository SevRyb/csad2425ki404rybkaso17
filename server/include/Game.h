#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <set>

#include "Data.h"
#include "Communicator.h"
#include "Board.h"
#include "Timer.h"


class Communicator;
class Timer;
/**
 * @class Game
 * @brief The main game logic class that handles the game state and updates
 */
class Game
{
public:
    /**
     * @brief Constructs a Game object with the provided Timer instance
     * @param timer The Timer instance to be used by the Game
     */
    Game(Timer* timer);
    /**
     * @brief Sets the Communicator instance for the Game
     * @param communicator The Communicator instance to be used by the Game
     */
    void setCommunicator(Communicator* communicator);

    /**
     * @brief Handles the start of a new game with the specified play mode
     * @param mode The play mode for the new game
     */
    void onNew(PlayMode mode);
    /**
     * @brief Handles a player's choice of a cell
     * @param cellId The identifier of the chosen cell
     */
    void onPlayerChoice(int cellId);
    /**
     * @brief Handles the loading of a saved game
     */
    void onLoad();
    /**
     * @brief Handles the saving of the current game
     */
    void onSave();
    /**
     * @brief Handles the game logic on timer callback event
     */
    void onTimer();

private:
    /**
     * @brief Resets the game board to its initial state
     */
    void resetBoard();
    /**
     * @brief Handles a player's move on the game board
     * @param cellId The identifier of the chosen cell
     */
    void move(int cellId);
    /**
     * @brief Checks if a player has won the game after a move
     * @param cellId The identifier of the cell where the move was made
     * @param state The state of the chosen cell ('x', 'o', or ' ')
     */
    void checkWin(int cellId, char state);
    /**
     * @brief Handles the end of the game and declares the winner
     * @param winner The index of the winning player (0 for 'x', 1 for 'o', 2 for draw)
     */
    void over(int winner);
    /**
     * @brief Starts the game
     */
    void start();
    /**
     * @brief Stops the game
     */
    void stop();

    Communicator* m_communicator;
    Timer* m_timer;

    PlayMode m_currentPlayMode;
    Board m_board;
    bool m_playerTurn;
};


#endif //GAME_H