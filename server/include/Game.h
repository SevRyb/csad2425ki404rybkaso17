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
class Game
{
public:
    Game(Timer* timer);
    void setCommunicator(Communicator* communicator);

    void onNew(PlayMode mode);
    void onPlayerChoice(int cellId);
    void onLoad();
    void onSave();
    void onTimer();

private:
    void resetBoard();
    void move(int cellId);
    void checkWin(int cellId, char state);
    void over(int winner);
    void start();
    void stop();

    Communicator* m_communicator;
    Timer* m_timer;

    PlayMode m_currentPlayMode;
    Board m_board;
    bool m_playerTurn;
};


#endif //GAME_H