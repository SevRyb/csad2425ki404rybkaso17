#ifndef BOARD_H
#define BOARD_H

#include <Arduino.h>
#include <set>

/**
 * @class Board
 * @brief Represents the game board, which is a 3x3 grid of cells
 */
class Board
{
public:
    /**
     * @brief Constructs a new Board object and initializes the board to an empty state
     */
    Board();
    /**
     * @brief Clears the board, setting all cells to the empty state
     */
    void clear();
    /**
     * @brief Places a cell on the board
     * @param id The identifier of the cell to be placed
     * @return True if the cell was successfully placed, false otherwise
     */
    bool placeCell(int id);
    /**
     * @brief Checks if there are any empty cells on the board
     * @return True if there are empty cells, false otherwise
     */
    bool hasEmptyCells();
    /**
     * @brief Selects a random empty cell on the board
     * @return The identifier of the randomly selected empty cell
     */
    int randomCell();
    /**
     * @brief Gets the state of a cell on the board
     * @param id The identifier of the cell
     * @return The state of the cell ('x', 'o', or ' ')
     */
    char get(int id);
    /**
     * @brief Gets the state of a cell on the board
     * @param x The column index of the cell
     * @param y The row index of the cell
     * @return The state of the cell ('x', 'o', or ' ')
     */
    char get(int x, int y);
    /**
     * @brief Sets the state of a cell on the board
     * @param id The identifier of the cell
     * @param c The new state of the cell ('x', 'o', or ' ')
     */
    void set(int id, char c);
    /**
     * @brief Sets the state of a cell on the board
     * @param x The column index of the cell
     * @param y The row index of the cell
     * @param c The new state of the cell ('x', 'o', or ' ')
     */
    void set(int x, int y, char c);
    /**
     * @brief Gets a pointer to the raw board data
     * @return A pointer to the raw board data
     */
    char *data();
    /**
     * @brief Loads the board state from a character array
     * @param data The character array containing the board state
     */
    void load(char* data);

    /**
     * @brief Converts a cell identifier to its corresponding column and row indices
     * @param id The cell identifier
     * @param x The variable to store the column index
     * @param y The variable to store the row index
     */
    static void idToXY(int id, int& x, int& y) 
    {
        x = id % 3;
        y = id / 3;
    };

    /**
     * @brief Converts column and row indices to a cell identifier
     * @param x The column index
     * @param y The row index
     * @return The cell identifier
     */
    static int xyToId(int x, int y) 
    {
        return y * 3 + x;
    };

private:
    char m_boardCells[9];
    std::set<int> m_remainingCells;
};

#endif //BOARD_H