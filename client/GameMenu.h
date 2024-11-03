#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "GameHost.h"

class GameMenu : public QWidget
{
    Q_OBJECT
public:
    explicit GameMenu(QWidget *parent = nullptr);



signals:

private slots:


private:
    QVBoxLayout *m_rootLay;
    QPushButton *m_manVsAIBtn;
    QPushButton *m_manVsManBtn;
    QPushButton *m_AIVsAIBtn;

};

#endif // GAMEMENU_H
