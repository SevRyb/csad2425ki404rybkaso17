#include "Game.h"
#include <LittleFS.h>


Game::Game(Timer* timer)
{
    m_timer = timer;
    m_timer->setCallback(std::bind(&Game::onTimer, this));
    resetBoard();
}

void Game::setCommunicator(Communicator* communicator)
{
    m_communicator = communicator;
}

void Game::onNew(PlayMode mode)
{
    m_currentPlayMode = mode;
    resetBoard();
    m_communicator->notifyGameStarted(mode);
    start();
}

void Game::onPlayerChoice(int cellId)
{
    if (m_currentPlayMode == PlayMode::Man_Man)
    {
        move(cellId);
    }
    else if (m_currentPlayMode == PlayMode::Man_AI)
    {
        if (!m_playerTurn)
        {
            move(cellId);
            delay(500);
            move(m_board.randomCell());
        }
    }
}

void Game::onLoad()
{
    const char fileName[] = "game";
    File file;
	if (LittleFS.exists(fileName))
	{
		file = LittleFS.open(fileName, "r");
        if (file)
        {
            file.readBytes((char*)&m_currentPlayMode, sizeof(int));
            file.readBytes((char*)&m_playerTurn, sizeof(int));
            char buff[9];
            file.readBytes(buff, 9);
            file.close();
            m_board.load(buff);
            m_communicator->notifyGameLoaded(m_board.data());
            start();
        }
	}
}

void Game::onSave()
{
    const char fileName[] = "game";
    File file;
    file = LittleFS.open(fileName, "w");
    file.write((char*)&m_currentPlayMode, sizeof(int));
    file.write((char*)&m_playerTurn, sizeof(int));
    file.write(m_board.data(), 9);
    file.close();
    stop();
}

void Game::onTimer()
{
    move(m_board.randomCell());
}

void Game::resetBoard()
{
    m_playerTurn = false;
    m_board.clear();
}

void Game::move(int cellId)
{
    if (m_board.placeCell(cellId) && m_currentPlayMode != PlayMode::Idle)
    {
        const char state = m_playerTurn ? 'o' : 'x';

        m_board.set(cellId, state);
        m_communicator->notifyPlayerChoice(cellId, state);
        
        checkWin(cellId, state);

        m_playerTurn = !m_playerTurn;
    }
}

void Game::checkWin(int cellId, char state)
{
    int x, y;
    Board::idToXY(cellId, x, y);
    // Check column
    for (int i = 0; i < 3; ++i)
    {
        if (m_board.get(x, i) != state)
            break;
        if (i == 3-1)
        {
            //m_communicator->notifyGameOver(m_playerTurn);
            over(m_playerTurn);
            return;
        }
    }
    // Check row
    for (int i = 0; i < 3; ++i)
    {
        if (m_board.get(i, y) != state)
            break;
        if (i == 3-1)
        {
            //m_communicator->notifyGameOver(m_playerTurn);
            over(m_playerTurn);
            return;
        }
    }
    // Check diagonal
    if (x == y)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (m_board.get(i, i) != state)
                break;
            if (i == 3-1)
            {
                //m_communicator->notifyGameOver(m_playerTurn);
                over(m_playerTurn);
                return;
            }
        }
    }
    // Check anti diagonal
    if (x + y == 3 - 1)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (m_board.get(i, (3 - 1) - i) != state)
                break;
            if (i == 3-1)
            {
                //m_communicator->notifyGameOver(m_playerTurn);
                over(m_playerTurn);
                return;
            }
        }
    }
    // Check draw
    if (!m_board.hasEmptyCells())
        over(2);
}

void Game::over(int winner)
{
    stop();
    m_communicator->notifyGameOver(winner);
}

void Game::start()
{
    if (m_currentPlayMode == PlayMode::AI_AI)
        m_timer->start();
}

void Game::stop()
{
    if (m_currentPlayMode == PlayMode::AI_AI)
        m_timer->stop();
    m_currentPlayMode = PlayMode::Idle;
}
