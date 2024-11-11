#ifndef BOARD_H
#define BOARD_H

#include <Arduino.h>
#include <set>

class Board
{
public:
    Board();
    void clear();
    bool placeCell(int id);
    bool hasEmptyCells();
    int randomCell();
    char get(int id);
    char get(int x, int y);
    void set(int id, char c);
    void set(int x, int y, char c);
    char *data();
    void load(char* data);

    static void idToXY(int id, int& x, int& y) 
    {
        x = id % 3;
        y = id / 3;
    };

    static int xyToId(int x, int y) 
    {
        return y * 3 + x;
    };

private:
    char m_boardCells[9];
    std::set<int> m_remainingCells;
};

#endif //BOARD_H