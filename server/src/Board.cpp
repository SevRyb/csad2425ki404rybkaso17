#include "Board.h"

Board::Board()
{
    clear();
}

void Board::clear()
{
    randomSeed(millis() + analogRead(A0));
    m_remainingCells.clear();
    for(int i = 0; i < 9; ++i) 
        m_remainingCells.insert(i);
    memset(m_boardCells, ' ', 9);
}

bool Board::placeCell(int id)
{
    // If cell is empty returns true
    if (m_remainingCells.contains(id))
    {
        m_remainingCells.erase(id);
        return true;
    }
    return false;
}

bool Board::hasEmptyCells()
{
    return !m_remainingCells.empty();
}

int Board::randomCell()
{
    return *std::next(m_remainingCells.begin(), random(0, m_remainingCells.size()));
}

char *Board::data()
{
    return m_boardCells;
}

void Board::load(char *data)
{
    memcpy(m_boardCells, data, 9);
    m_remainingCells.clear();
    for(int i = 0; i < 9; ++i) 
    {
        if (m_boardCells[i] == ' ')
            m_remainingCells.insert(i);
    }
}

char Board::get(int id)
{
    return m_boardCells[id];
}

char Board::get(int x, int y)
{
    return m_boardCells[xyToId(x, y)];
}

void Board::set(int id, char c)
{
    m_boardCells[id] = c;
}

void Board::set(int x, int y, char c)
{
    m_boardCells[xyToId(x, y)] = c;
}
