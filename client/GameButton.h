#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QSvgRenderer>

class GameButton : public QPushButton
{
    Q_OBJECT
public:
    explicit GameButton(int id, QWidget *parent = nullptr);
    void setState(char state);
    int id();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent  *event) override;

signals:
    void hit(int id);

private:
    int m_id;
    char m_state;

    QSvgRenderer m_svgRenderer;
    bool m_renderState;
};

#endif // GAMEBUTTON_H
