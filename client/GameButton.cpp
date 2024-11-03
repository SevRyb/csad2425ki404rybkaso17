#include "GameButton.h"

#include <QDebug>

GameButton::GameButton(int id, QWidget *parent)
    : QPushButton{parent}
{
    m_id = id;
    m_state = ' ';
    m_renderState = false;
}

void GameButton::setState(char state)
{
    m_state = state;
    if (state == 'x' || state == 'o')
    {
        m_svgRenderer.load(QString(":/%1.svg").arg(state));
        m_renderState = true;
    }
    else
        m_renderState = false;
    repaint();
}

int GameButton::id()
{
    return m_id;
}

void GameButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setBrush(QColor(40, 40, 40));
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, size().width(), size().height());

    if (m_renderState)
        m_svgRenderer.render(&painter);

}

void GameButton::mouseReleaseEvent(QMouseEvent *event)
{
    QPushButton::mouseReleaseEvent(event);
    emit hit(m_id);
}
