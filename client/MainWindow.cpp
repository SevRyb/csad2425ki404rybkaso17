#include "MainWindow.h"

#include "GameHost.h"

#include <QLabel>
#include <QMessageBox>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Tic-Tac-Toe");
    resize(800, 800);
    setWindowIcon(QIcon(":/icon.png"));

    g_GameHost::Instance();

    m_rootWidget = new QWidget(this);
    m_rootLay = new QStackedLayout(m_rootWidget);
    setCentralWidget(m_rootWidget);
    setStyleSheet("QWidget {"
                  "background: rgb(108, 68, 188);"
                  "}"
                  "QPushButton {"
                  "color: rgb(108, 68, 188);"
                  "background: rgb(40, 40, 40);"
                  "border: none;"
                  "font: 40pt;"
                  "}"
                  "QPushButton:hover {"
                  "border: 5px solid rgb(108, 68, 188);"
                  "}");

    /* Main Menu */
    m_mainMenuWidget = new QWidget(this);
    m_mainMenuLay = new QVBoxLayout(m_mainMenuWidget);

    m_newBtn = new QPushButton("New", this);
    m_newBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_loadBtn = new QPushButton("Load", this);
    m_loadBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_saveBtn = new QPushButton("Save", this);
    m_saveBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_mainMenuLay->addWidget(m_newBtn);
    m_mainMenuLay->addWidget(m_loadBtn);
    m_mainMenuLay->addWidget(m_saveBtn);

    /* Play Mode Menu */
    m_playModeMenuWidget = new QWidget(this);
    m_playModeMenuLay = new QVBoxLayout(m_playModeMenuWidget);

    m_manVsAIBtn = new QPushButton("Man vs AI", this);
    m_manVsAIBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_manVsManBtn = new QPushButton("Man vs Man", this);
    m_manVsManBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_AIVsAIBtn = new QPushButton("AI vs AI", this);
    m_AIVsAIBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_playModeMenuLay->addWidget(m_manVsAIBtn);
    m_playModeMenuLay->addWidget(m_manVsManBtn);
    m_playModeMenuLay->addWidget(m_AIVsAIBtn);

    /* Game Board */
    m_gameBoard = new GameBoard(this);

    m_rootLay->addWidget(m_mainMenuWidget);
    m_rootLay->addWidget(m_playModeMenuWidget);
    m_rootLay->addWidget(m_gameBoard);


    /* CONNECTIONS */
    /* Main Menu */
    connect(m_newBtn, &QPushButton::released, this, &MainWindow::onNewBtn);
    connect(m_loadBtn, &QPushButton::released, this, &MainWindow::onLoadBtn);
    connect(m_saveBtn, &QPushButton::released, this, &MainWindow::onSaveBtn);
    /* Play Mode Menu */
    connect(m_manVsAIBtn, &QPushButton::released, this, &MainWindow::onManVsAIBtn);
    connect(m_manVsManBtn, &QPushButton::released, this, &MainWindow::onManVsManBtn);
    connect(m_AIVsAIBtn, &QPushButton::released, this, &MainWindow::onAIVsAIBtn);
    /* Shortcuts */
    QKeySequence backKeySequence = QKeySequence(Qt::Key_Escape);
    QShortcut *backSchortcut = new QShortcut(backKeySequence, this);
    connect(backSchortcut, &QShortcut::activated, this, &MainWindow::onMainMenu);

    connect(g_GameHost::Instance(), &GameHost::sigGameStart, this, &MainWindow::onGameStart);
    connect(g_GameHost::Instance(), &GameHost::sigGameOver, this, &MainWindow::onGameOver);
    connect(g_GameHost::Instance(), &GameHost::sigLoadGame, this, &MainWindow::onLoadGame);

}

MainWindow::~MainWindow() {}

/* Main Menu */
void MainWindow::onNewBtn()
{
    m_rootLay->setCurrentIndex(1);
}

void MainWindow::onLoadBtn()
{
    g_GameHost::Instance()->reqLoadGame();
    //m_rootLay->setCurrentIndex(2);
}

void MainWindow::onSaveBtn()
{
    g_GameHost::Instance()->reqSaveGame();
}

/* Play Mode Menu */
void MainWindow::onManVsAIBtn()
{
    g_GameHost::Instance()->reqNewGame(PlayMode::Man_AI);
    //m_rootLay->setCurrentIndex(2);
}

void MainWindow::onManVsManBtn()
{
    g_GameHost::Instance()->reqNewGame(PlayMode::Man_Man);
    //m_rootLay->setCurrentIndex(2);
}

void MainWindow::onAIVsAIBtn()
{
    g_GameHost::Instance()->reqNewGame(PlayMode::AI_AI);
    //m_rootLay->setCurrentIndex(2);
}

void MainWindow::onMainMenu()
{
    m_rootLay->setCurrentIndex(0);
}

/* Responses from server */
void MainWindow::onGameStart(PlayMode mode)
{
    m_gameBoard->reset();
    m_rootLay->setCurrentIndex(2);
}

void MainWindow::onGameOver(int winner)
{
    switch (winner)
    {
    case 0:
        QMessageBox::information(NULL, "Game Over", "The X's won!");
        break;
    case 1:
        QMessageBox::information(NULL, "Game Over", "The O's won!");
        break;
    case 2:
        QMessageBox::information(NULL, "Game Over", "Nobody won. Draw!");
        break;
    default:
        break;
    }
}

void MainWindow::onLoadGame(const QString &cells)
{
    m_gameBoard->load(cells);
    m_rootLay->setCurrentIndex(2);
}
