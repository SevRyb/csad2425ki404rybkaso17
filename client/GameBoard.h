#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QPainter>
#include <QVector>

#include "GameButton.h"

class GameBoard : public QWidget
{
    Q_OBJECT
public:
    explicit GameBoard(QWidget *parent = nullptr);
    void reset();
    void load(const QString &cells);

protected:
    void paintEvent(QPaintEvent *event) override;

public slots:
    void onPlayerChoice(int cellId, signed char cellState);

private:
    QGridLayout *m_rootLay;

    QVector<GameButton*> m_cellBtns;
};

#endif // GAMEBOARD_H
