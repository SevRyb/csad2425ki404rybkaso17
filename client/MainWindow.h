#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QPushButton>

#include "GameBoard.h"
#include "GameHost.h"


//#ifdef UNDER_TESTING
//#define PRIVATE_TESTABLE public
//#else
//#define PRIVATE_TESTABLE private
//#endif


/**
 * @class MainWindow
 * @brief The main window of the application
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the MainWindow
     * @param parent The parent widget (default is nullptr)
     */
    MainWindow(QWidget *parent = nullptr);
    /**
     * @brief Destroys the MainWindow
     */
    ~MainWindow();

#ifdef UNDER_TESTING
    /**
     * @brief Returns current page index
     * @return Current page index
     */
    int currentPageIndex()
    {
        return m_rootLay->currentIndex();
    };
#endif

#ifndef UNDER_TESTING
private slots:
#else
public slots:
#endif

    /* Main Menu */
    /**
     * @brief Handles the "New" button click
     */
    void onNewBtn();
    /**
     * @brief Handles the "Load" button click
     */
    void onLoadBtn();
    /**
     * @brief Handles the "Save" button click
     */
    void onSaveBtn();
    /* Play Mode Menu */
    /**
     * @brief Handles the "Man vs AI" button click
     */
    void onManVsAIBtn();
    /**
     * @brief Handles the "Man vs Man" button click
     */
    void onManVsManBtn();
    /**
     * @brief Handles the "AI vs AI" button click
     */
    void onAIVsAIBtn();
    /* Back to Main Menu */
    /**
     * @brief Handles the navigation back to the main menu
     */
    void onMainMenu();
    /* Responses from server */
    /**
     * @brief Handles the game start notification
     * @param mode The play mode of the game
     */
    void onGameStart(PlayMode mode);
    /**
     * @brief Handles the game over notification
     * @param winner The index of the winning player (0 for 'x', 1 for 'o', 2 for draw)
     */
    void onGameOver(int winner);
    /**
     * @brief Handles the game load notification
     * @param cells The saved game state
     */
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
