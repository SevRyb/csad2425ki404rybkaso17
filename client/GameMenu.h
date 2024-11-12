#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "GameHost.h"

/**
 * @class GameMenu
 * @brief The game menu widget, which allows the user to select the game mode
 */
class GameMenu : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the GameMenu widget
     * @param parent The parent widget (default is nullptr)
     */
    explicit GameMenu(QWidget *parent = nullptr);

private:
    QVBoxLayout *m_rootLay;
    QPushButton *m_manVsAIBtn;
    QPushButton *m_manVsManBtn;
    QPushButton *m_AIVsAIBtn;
};

#endif // GAMEMENU_H
