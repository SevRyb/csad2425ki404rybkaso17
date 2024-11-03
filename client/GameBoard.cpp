#include "GameBoard.h"
#include "GameHost.h"

#include <QVectorIterator>

GameBoard::GameBoard(QWidget *parent)
    : QWidget{parent}
{
    m_rootLay = new QGridLayout;
    setLayout(m_rootLay);

    m_cellBtns.reserve(9);

    int cellId = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            GameButton *cellBtn = new GameButton(cellId, this);
            cellBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            m_rootLay->addWidget(cellBtn, i, j);

            m_cellBtns.append(cellBtn);
            connect(cellBtn, &GameButton::hit, g_GameHost::Instance(), &GameHost::reqPlayerChoice);

            ++cellId;
        }
    }


    /* CONNECTIONS */
    connect(g_GameHost::Instance(), &GameHost::sigPlayerChoice, this, &GameBoard::onPlayerChoice);
}

void GameBoard::reset()
{
    QVectorIterator<GameButton*> it(m_cellBtns);
    while (it.hasNext())
    {
        it.next()->setState(' ');
    }
}

void GameBoard::load(const QString &cells)
{
    for (int i = 0; i < 9; ++i)
    {
        m_cellBtns.at(i)->setState(cells.at(i).toLatin1());
    }
}

void GameBoard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QColor(108, 68, 188));
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, size().width(), size().height());
}

void GameBoard::onPlayerChoice(int cellId, signed char cellState)
{
    m_cellBtns.at(cellId)->setState(cellState);
}
