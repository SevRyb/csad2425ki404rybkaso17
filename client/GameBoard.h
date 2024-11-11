#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QPainter>
#include <QVector>

#include "GameButton.h"

/**
 * @class GameBoard
 * @brief The game board widget, which manages the game buttons and board layout
 */
class GameBoard : public QWidget
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructs the GameBoard widget
     * @param parent The parent widget (default is nullptr)
     */
    explicit GameBoard(QWidget *parent = nullptr);
    /**
     * @brief Resets the game board to its initial state
     */
    void reset();
    /**
     * @brief Loads the game state from a string of cells
     * @param cells The string representation of the game state
     */
    void load(const QString &cells);

protected:
    /**
     * @brief Overrides the paintEvent to draw the game board background
     * @param event The paint event
     */
    void paintEvent(QPaintEvent *event) override;

public slots:
    /**
     * @brief Handles the player's choice of a cell
     * @param cellId The identifier of the chosen cell
     * @param cellState The state of the chosen cell ('x', 'o', or ' ')
     */
    void onPlayerChoice(int cellId, signed char cellState);

private:
    QGridLayout *m_rootLay;

    QVector<GameButton*> m_cellBtns;
};

#endif // GAMEBOARD_H
