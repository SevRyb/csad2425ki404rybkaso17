#include <QTest>
#include <QSignalSpy>

#include "../MainWindow.h"


class SwClientUT : public QObject
{
    Q_OBJECT

private slots:
    // Tests:
    // GameHost::detectHostSerialPort, GameHost::isSerialPortOpen
    void initTestCase()
    {
        m_magickNumber = 5;
        m_mainWindow = new MainWindow;  // Implicitly calls GameHost::detectHostSerialPort
        QVERIFY(g_GameHost::Instance()->isSerialPortOpen());
    }

    // Tests:
    // GameHost::closeSerialPort
    void cleanupTestCase()
    {
        g_GameHost::Instance()->closeSerialPort();
    }

    // Tests:
    // MainWindow::onMainMenu
    void testMainMenuPage()
    {
        m_mainWindow->onMainMenu();
        QCOMPARE(m_mainWindow->currentPageIndex(), 0);
    }

    // Tests:
    // MainWindow::onNewBtn
    void testNewGamePage()
    {
        m_mainWindow->onNewBtn();
        QCOMPARE(m_mainWindow->currentPageIndex(), 1);
    }

    // Tests:
    // MainWindow::onManVsAIBtn, MainWindow::onGameStart, GameHost::reqNewGame, GameHost::sigGameStart
    void testGameStartManVsAI()
    {
        m_mainWindow->onManVsAIBtn();
        QSignalSpy signalSpy(g_GameHost::Instance(), &GameHost::sigGameStart);  // Emits MainWindow::onGameStart
        QVERIFY(signalSpy.wait(3000));
        QCOMPARE(signalSpy.count(), 1);
        QCOMPARE(m_mainWindow->currentPageIndex(), 2);
    }

    // Tests:
    // MainWindow::onManVsManBtn, MainWindow::onGameStart, GameHost::reqNewGame, GameHost::sigGameStart
    void testGameStartManVsMan()
    {
        m_mainWindow->onManVsManBtn();
        QSignalSpy signalSpy(g_GameHost::Instance(), &GameHost::sigGameStart);  // Emits MainWindow::onGameStart
        QVERIFY(signalSpy.wait(3000));
        QCOMPARE(signalSpy.count(), 1);
        QCOMPARE(m_mainWindow->currentPageIndex(), 2);
    }

    // Tests:
    // MainWindow::onAIVsAIBtn, MainWindow::onGameStart, GameHost::reqNewGame, GameHost::sigGameStart
    void testGameStartAIVsAI()
    {
        m_mainWindow->onManVsAIBtn();
        QSignalSpy signalSpy(g_GameHost::Instance(), &GameHost::sigGameStart);  // Emits MainWindow::onGameStart
        QVERIFY(signalSpy.wait(3000));
        QCOMPARE(signalSpy.count(), 1);
        QCOMPARE(m_mainWindow->currentPageIndex(), 2);
    }

    // Tests:
    // MainWindow::onLoadBtn, MainWindow::onLoadGame, GameHost::reqLoadGame, GameHost::sigLoadGame
    void testLoadGame()
    {
        m_mainWindow->onLoadBtn();
        QSignalSpy signalSpy(g_GameHost::Instance(), &GameHost::sigLoadGame);  // Emits MainWindow::onLoadGame
        QVERIFY(signalSpy.wait(3000));
        QCOMPARE(signalSpy.count(), 1);
        QCOMPARE(m_mainWindow->currentPageIndex(), 2);
    }

    // Tests:
    // MainWindow::onSaveBtn, GameHost::reqSaveGame
    void testSaveGame()
    {
        m_mainWindow->onSaveBtn();
    }

    // Tests:
    // GameHost::sigPlayerChoice, GameBoard::onPlayerChoice, GameBoard::reqPlayerChoice,
    // GameHost::sigGameOver, MainWindow::onGameOver
    void testXWin()
    {
        QSignalSpy *signalSpy;

        g_GameHost::Instance()->reqNewGame(PlayMode::Man_Man);
        signalSpy = new QSignalSpy(g_GameHost::Instance(), &GameHost::sigGameStart);  // Emits MainWindow::onGameStart
        QVERIFY(signalSpy->wait(3000));
        QCOMPARE(signalSpy->count(), 1);

        int cellId;
        char cellState;
        // Place "x" at (0, 0)
        {
            cellId = 0;
            cellState = 'x';
            g_GameHost::Instance()->reqPlayerChoice(cellId);

            QSignalSpy _signalSpy(g_GameHost::Instance(), &GameHost::sigPlayerChoice);  // Emits GameBoard::onPlayerChoice
            QVERIFY(_signalSpy.wait(3000));
            QCOMPARE(_signalSpy.count(), 1);

            QList<QVariant> arguments = _signalSpy.takeFirst();
            QVERIFY(arguments.count() == 2);
            QCOMPARE(arguments.at(0).toInt(), cellId);
            QCOMPARE(arguments.at(1).toChar(), cellState);
        }
        // Place "o" at (1, 0)
        {
            cellId = 1;
            cellState = 'o';
            g_GameHost::Instance()->reqPlayerChoice(cellId);

            QSignalSpy _signalSpy(g_GameHost::Instance(), &GameHost::sigPlayerChoice);  // Emits GameBoard::onPlayerChoice
            QVERIFY(_signalSpy.wait(3000));
            QCOMPARE(_signalSpy.count(), 1);

            QList<QVariant> arguments = _signalSpy.takeFirst();
            QVERIFY(arguments.count() == 2);
            QCOMPARE(arguments.at(0).toInt(), cellId);
            QCOMPARE(arguments.at(1).toChar(), cellState);
        }
        // Place "x" at (1, 1)
        {
            cellId = 4;
            cellState = 'x';
            g_GameHost::Instance()->reqPlayerChoice(cellId);

            QSignalSpy _signalSpy(g_GameHost::Instance(), &GameHost::sigPlayerChoice);  // Emits GameBoard::onPlayerChoice
            QVERIFY(_signalSpy.wait(3000));
            QCOMPARE(_signalSpy.count(), 1);

            QList<QVariant> arguments = _signalSpy.takeFirst();
            QVERIFY(arguments.count() == 2);
            QCOMPARE(arguments.at(0).toInt(), cellId);
            QCOMPARE(arguments.at(1).toChar(), cellState);
        }
        // Place "o" at (2, 0)
        {
            cellId = 2;
            cellState = 'o';
            g_GameHost::Instance()->reqPlayerChoice(cellId);

            QSignalSpy _signalSpy(g_GameHost::Instance(), &GameHost::sigPlayerChoice);  // Emits GameBoard::onPlayerChoice
            QVERIFY(_signalSpy.wait(3000));
            QCOMPARE(_signalSpy.count(), 1);

            QList<QVariant> arguments = _signalSpy.takeFirst();
            QVERIFY(arguments.count() == 2);
            QCOMPARE(arguments.at(0).toInt(), cellId);
            QCOMPARE(arguments.at(1).toChar(), cellState);
        }
        // Place "x" at (2, 2)
        {
            cellId = 8;
            cellState = 'x';
            g_GameHost::Instance()->reqPlayerChoice(cellId);

            QSignalSpy _signalSpy(g_GameHost::Instance(), &GameHost::sigPlayerChoice);  // Emits GameBoard::onPlayerChoice
            QVERIFY(_signalSpy.wait(3000));
            QCOMPARE(_signalSpy.count(), 1);

            QList<QVariant> arguments = _signalSpy.takeFirst();
            QVERIFY(arguments.count() == 2);
            QCOMPARE(arguments.at(0).toInt(), cellId);
            QCOMPARE(arguments.at(1).toChar(), cellState);
        }

        signalSpy = new QSignalSpy(g_GameHost::Instance(), &GameHost::sigGameOver);  // Emits MainWindow::onGameOver
        QVERIFY(signalSpy->wait(3000));
        QCOMPARE(signalSpy->count(), 1);

        QList<QVariant> arguments = signalSpy->takeFirst();
        QVERIFY(arguments.count() == 1);
        QCOMPARE(arguments.at(0).toInt(), 0);  // 0 for 'x', 1 for 'o', 2 for draw
    }

    // Tests:
    // GameHost::sigPlayerChoice, GameBoard::onPlayerChoice, GameBoard::reqPlayerChoice,
    // GameHost::sigGameOver, MainWindow::onGameOver
    void testOWin()
    {
        QSignalSpy *signalSpy;

        g_GameHost::Instance()->reqNewGame(PlayMode::Man_Man);
        signalSpy = new QSignalSpy(g_GameHost::Instance(), &GameHost::sigGameStart);  // Emits MainWindow::onGameStart
        QVERIFY(signalSpy->wait(3000));
        QCOMPARE(signalSpy->count(), 1);

        int cellId;
        char cellState;
        // Place "x" at (0, 1)
        {
            cellId = 3;
            cellState = 'x';
            g_GameHost::Instance()->reqPlayerChoice(cellId);

            QSignalSpy _signalSpy(g_GameHost::Instance(), &GameHost::sigPlayerChoice);  // Emits GameBoard::onPlayerChoice
            QVERIFY(_signalSpy.wait(3000));
            QCOMPARE(_signalSpy.count(), 1);

            QList<QVariant> arguments = _signalSpy.takeFirst();
            QVERIFY(arguments.count() == 2);
            QCOMPARE(arguments.at(0).toInt(), cellId);
            QCOMPARE(arguments.at(1).toChar(), cellState);
        }
        // Place "o" at (0, 0)
        {
            cellId = 0;
            cellState = 'o';
            g_GameHost::Instance()->reqPlayerChoice(cellId);

            QSignalSpy _signalSpy(g_GameHost::Instance(), &GameHost::sigPlayerChoice);  // Emits GameBoard::onPlayerChoice
            QVERIFY(_signalSpy.wait(3000));
            QCOMPARE(_signalSpy.count(), 1);

            QList<QVariant> arguments = _signalSpy.takeFirst();
            QVERIFY(arguments.count() == 2);
            QCOMPARE(arguments.at(0).toInt(), cellId);
            QCOMPARE(arguments.at(1).toChar(), cellState);
        }
        // Place "x" at (1, 0)
        {
            cellId = 1;
            cellState = 'x';
            g_GameHost::Instance()->reqPlayerChoice(cellId);

            QSignalSpy _signalSpy(g_GameHost::Instance(), &GameHost::sigPlayerChoice);  // Emits GameBoard::onPlayerChoice
            QVERIFY(_signalSpy.wait(3000));
            QCOMPARE(_signalSpy.count(), 1);

            QList<QVariant> arguments = _signalSpy.takeFirst();
            QVERIFY(arguments.count() == 2);
            QCOMPARE(arguments.at(0).toInt(), cellId);
            QCOMPARE(arguments.at(1).toChar(), cellState);
        }
        // Place "o" at (1, 1)
        {
            cellId = 4;
            cellState = 'o';
            g_GameHost::Instance()->reqPlayerChoice(cellId);

            QSignalSpy _signalSpy(g_GameHost::Instance(), &GameHost::sigPlayerChoice);  // Emits GameBoard::onPlayerChoice
            QVERIFY(_signalSpy.wait(3000));
            QCOMPARE(_signalSpy.count(), 1);

            QList<QVariant> arguments = _signalSpy.takeFirst();
            QVERIFY(arguments.count() == 2);
            QCOMPARE(arguments.at(0).toInt(), cellId);
            QCOMPARE(arguments.at(1).toChar(), cellState);
        }
        // Place "x" at (0, 2)
        {
            cellId = 6;
            cellState = 'x';
            g_GameHost::Instance()->reqPlayerChoice(cellId);

            QSignalSpy _signalSpy(g_GameHost::Instance(), &GameHost::sigPlayerChoice);  // Emits GameBoard::onPlayerChoice
            QVERIFY(_signalSpy.wait(3000));
            QCOMPARE(_signalSpy.count(), 1);

            QList<QVariant> arguments = _signalSpy.takeFirst();
            QVERIFY(arguments.count() == 2);
            QCOMPARE(arguments.at(0).toInt(), cellId);
            QCOMPARE(arguments.at(1).toChar(), cellState);
        }
        // Place "o" at (2, 2)
        {
            cellId = 8;
            cellState = 'o';
            g_GameHost::Instance()->reqPlayerChoice(cellId);

            QSignalSpy _signalSpy(g_GameHost::Instance(), &GameHost::sigPlayerChoice);  // Emits GameBoard::onPlayerChoice
            QVERIFY(_signalSpy.wait(3000));
            QCOMPARE(_signalSpy.count(), 1);

            QList<QVariant> arguments = _signalSpy.takeFirst();
            QVERIFY(arguments.count() == 2);
            QCOMPARE(arguments.at(0).toInt(), cellId);
            QCOMPARE(arguments.at(1).toChar(), cellState);
        }

        signalSpy = new QSignalSpy(g_GameHost::Instance(), &GameHost::sigGameOver);  // Emits MainWindow::onGameOver
        QVERIFY(signalSpy->wait(3000));
        QCOMPARE(signalSpy->count(), 1);

        QList<QVariant> arguments = signalSpy->takeFirst();
        QVERIFY(arguments.count() == 1);
        QCOMPARE(arguments.at(0).toInt(), 1);  // 0 for 'x', 1 for 'o', 2 for draw
    }

    // Tests:
    // GameHost::sigPlayerChoice, GameBoard::onPlayerChoice, GameBoard::reqPlayerChoice,
    // GameHost::sigGameOver, MainWindow::onGameOver
    void testDraw()
    {
        QSignalSpy *signalSpy;

        g_GameHost::Instance()->reqNewGame(PlayMode::Man_Man);
        signalSpy = new QSignalSpy(g_GameHost::Instance(), &GameHost::sigGameStart);  // Emits MainWindow::onGameStart
        QVERIFY(signalSpy->wait(3000));
        QCOMPARE(signalSpy->count(), 1);

        int cellId;
        char cellState;
        // Place "x" at (0, 0)
        {
            cellId = 0;
            cellState = 'x';
            g_GameHost::Instance()->reqPlayerChoice(cellId);

            QSignalSpy _signalSpy(g_GameHost::Instance(), &GameHost::sigPlayerChoice);  // Emits GameBoard::onPlayerChoice
            QVERIFY(_signalSpy.wait(3000));
            QCOMPARE(_signalSpy.count(), 1);

            QList<QVariant> arguments = _signalSpy.takeFirst();
            QVERIFY(arguments.count() == 2);
            QCOMPARE(arguments.at(0).toInt(), cellId);
            QCOMPARE(arguments.at(1).toChar(), cellState);
        }
        // Place "o" at (0, 1)
        {
            cellId = 3;
            cellState = 'o';
            g_GameHost::Instance()->reqPlayerChoice(cellId);

            QSignalSpy _signalSpy(g_GameHost::Instance(), &GameHost::sigPlayerChoice);  // Emits GameBoard::onPlayerChoice
            QVERIFY(_signalSpy.wait(3000));
            QCOMPARE(_signalSpy.count(), 1);

            QList<QVariant> arguments = _signalSpy.takeFirst();
            QVERIFY(arguments.count() == 2);
            QCOMPARE(arguments.at(0).toInt(), cellId);
            QCOMPARE(arguments.at(1).toChar(), cellState);
        }
        // Place "x" at (1, 0)
        {
            cellId = 1;
            cellState = 'x';
            g_GameHost::Instance()->reqPlayerChoice(cellId);

            QSignalSpy _signalSpy(g_GameHost::Instance(), &GameHost::sigPlayerChoice);  // Emits GameBoard::onPlayerChoice
            QVERIFY(_signalSpy.wait(3000));
            QCOMPARE(_signalSpy.count(), 1);

            QList<QVariant> arguments = _signalSpy.takeFirst();
            QVERIFY(arguments.count() == 2);
            QCOMPARE(arguments.at(0).toInt(), cellId);
            QCOMPARE(arguments.at(1).toChar(), cellState);
        }
        // Place "o" at (2, 0)
        {
            cellId = 2;
            cellState = 'o';
            g_GameHost::Instance()->reqPlayerChoice(cellId);

            QSignalSpy _signalSpy(g_GameHost::Instance(), &GameHost::sigPlayerChoice);  // Emits GameBoard::onPlayerChoice
            QVERIFY(_signalSpy.wait(3000));
            QCOMPARE(_signalSpy.count(), 1);

            QList<QVariant> arguments = _signalSpy.takeFirst();
            QVERIFY(arguments.count() == 2);
            QCOMPARE(arguments.at(0).toInt(), cellId);
            QCOMPARE(arguments.at(1).toChar(), cellState);
        }
        // Place "x" at (0, 2)
        {
            cellId = 6;
            cellState = 'x';
            g_GameHost::Instance()->reqPlayerChoice(cellId);

            QSignalSpy _signalSpy(g_GameHost::Instance(), &GameHost::sigPlayerChoice);  // Emits GameBoard::onPlayerChoice
            QVERIFY(_signalSpy.wait(3000));
            QCOMPARE(_signalSpy.count(), 1);

            QList<QVariant> arguments = _signalSpy.takeFirst();
            QVERIFY(arguments.count() == 2);
            QCOMPARE(arguments.at(0).toInt(), cellId);
            QCOMPARE(arguments.at(1).toChar(), cellState);
        }
        // Place "o" at (1, 1)
        {
            cellId = 4;
            cellState = 'o';
            g_GameHost::Instance()->reqPlayerChoice(cellId);

            QSignalSpy _signalSpy(g_GameHost::Instance(), &GameHost::sigPlayerChoice);  // Emits GameBoard::onPlayerChoice
            QVERIFY(_signalSpy.wait(3000));
            QCOMPARE(_signalSpy.count(), 1);

            QList<QVariant> arguments = _signalSpy.takeFirst();
            QVERIFY(arguments.count() == 2);
            QCOMPARE(arguments.at(0).toInt(), cellId);
            QCOMPARE(arguments.at(1).toChar(), cellState);
        }
        // Place "x" at (2, 1)
        {
            cellId = 5;
            cellState = 'x';
            g_GameHost::Instance()->reqPlayerChoice(cellId);

            QSignalSpy _signalSpy(g_GameHost::Instance(), &GameHost::sigPlayerChoice);  // Emits GameBoard::onPlayerChoice
            QVERIFY(_signalSpy.wait(3000));
            QCOMPARE(_signalSpy.count(), 1);

            QList<QVariant> arguments = _signalSpy.takeFirst();
            QVERIFY(arguments.count() == 2);
            QCOMPARE(arguments.at(0).toInt(), cellId);
            QCOMPARE(arguments.at(1).toChar(), cellState);
        }
        // Place "o" at (1, 2)
        {
            cellId = 7;
            cellState = 'o';
            g_GameHost::Instance()->reqPlayerChoice(cellId);

            QSignalSpy _signalSpy(g_GameHost::Instance(), &GameHost::sigPlayerChoice);  // Emits GameBoard::onPlayerChoice
            QVERIFY(_signalSpy.wait(3000));
            QCOMPARE(_signalSpy.count(), 1);

            QList<QVariant> arguments = _signalSpy.takeFirst();
            QVERIFY(arguments.count() == 2);
            QCOMPARE(arguments.at(0).toInt(), cellId);
            QCOMPARE(arguments.at(1).toChar(), cellState);
        }
        // Place "x" at (2, 2)
        {
            cellId = 8;
            cellState = 'x';
            g_GameHost::Instance()->reqPlayerChoice(cellId);

            QSignalSpy _signalSpy(g_GameHost::Instance(), &GameHost::sigPlayerChoice);  // Emits GameBoard::onPlayerChoice
            QVERIFY(_signalSpy.wait(3000));
            QCOMPARE(_signalSpy.count(), 1);

            QList<QVariant> arguments = _signalSpy.takeFirst();
            QVERIFY(arguments.count() == 2);
            QCOMPARE(arguments.at(0).toInt(), cellId);
            QCOMPARE(arguments.at(1).toChar(), cellState);
        }

        signalSpy = new QSignalSpy(g_GameHost::Instance(), &GameHost::sigGameOver);  // Emits MainWindow::onGameOver
        QVERIFY(signalSpy->wait(3000));
        QCOMPARE(signalSpy->count(), 1);

        QList<QVariant> arguments = signalSpy->takeFirst();
        QVERIFY(arguments.count() == 1);
        QCOMPARE(arguments.at(0).toInt(), 2);  // 0 for 'x', 1 for 'o', 2 for draw
    }

    void testConnection()
    {
        g_GameHost::Instance()->reqTestConnection(m_magickNumber);

        QSignalSpy signalSpy(g_GameHost::Instance(), &GameHost::sigTestConnection);
        QVERIFY(signalSpy.wait(5000));
        QCOMPARE(signalSpy.count(), 1);

        QList<QVariant> arguments = signalSpy.takeFirst();
        QVERIFY(arguments.count() == 2);
        QVERIFY(arguments.at(0).type() == QVariant::Int);
        QVERIFY(arguments.at(1).type() == QVariant::String);

        QCOMPARE((arguments.at(0).toInt() - 123) / 2, m_magickNumber);
        QCOMPARE(arguments.at(1).toString(), "TicTacToe#3x3");
    }

private:
    MainWindow *m_mainWindow;
    int m_magickNumber;
};

QTEST_MAIN(SwClientUT)

#include "UTSwClient.moc"
