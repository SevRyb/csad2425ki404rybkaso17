#include "GameMenu.h"

#include <functional>

GameMenu::GameMenu(QWidget *parent)
    : QWidget{parent}
{
    m_rootLay = new QVBoxLayout(this);

    m_manVsAIBtn = new QPushButton("Man vs AI", this);
    m_manVsAIBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_manVsManBtn = new QPushButton("Man vs Man", this);
    m_manVsManBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_AIVsAIBtn = new QPushButton("AI vs AI", this);
    m_AIVsAIBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_rootLay->addWidget(m_manVsAIBtn);
    m_rootLay->addWidget(m_manVsManBtn);
    m_rootLay->addWidget(m_AIVsAIBtn);

    /* CONNECTIONS */
    connect(m_manVsAIBtn, &QPushButton::released,
            std::bind(&GameHost::reqNewGame, g_GameHost::Instance(), PlayMode::Man_AI));
    connect(m_manVsManBtn, &QPushButton::released,
            std::bind(&GameHost::reqNewGame, g_GameHost::Instance(), PlayMode::Man_Man));
    connect(m_AIVsAIBtn, &QPushButton::released,
            std::bind(&GameHost::reqNewGame, g_GameHost::Instance(), PlayMode::AI_AI));

}
