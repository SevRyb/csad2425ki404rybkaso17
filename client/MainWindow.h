#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QPushButton>

#include "GameBoard.h"
#include "GameHost.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /* Main Menu */
    void onNewBtn();
    void onLoadBtn();
    void onSaveBtn();
    /* Play Mode Menu */
    void onManVsAIBtn();
    void onManVsManBtn();
    void onAIVsAIBtn();
    /* Back to Main Menu */
    void onMainMenu();
    /* Responses from server */
    void onGameStart(PlayMode mode);
    void onGameOver(int winner);
    void onLoadGame(const QString &cells);

private:
    QWidget *m_rootWidget;
    QStackedLayout *m_rootLay;

    GameBoard *m_gameBoard;

    /* Main Menu */
    QWidget *m_mainMenuWidget;
    QVBoxLayout *m_mainMenuLay;
    QPushButton *m_newBtn;
    QPushButton *m_loadBtn;
    QPushButton *m_saveBtn;
    /* Play Mode Menu */
    QWidget *m_playModeMenuWidget;
    QVBoxLayout *m_playModeMenuLay;
    QPushButton *m_manVsAIBtn;
    QPushButton *m_manVsManBtn;
    QPushButton *m_AIVsAIBtn;

};
#endif // MAINWINDOW_H
