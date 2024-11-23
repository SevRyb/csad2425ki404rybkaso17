
#ifndef GAMEHOST_H
#define GAMEHOST_H


#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "Data.h"
#include "Singleton.h"


/**
 * @class GameHost
 * @brief The game host class responsible for communicating with the game server
 */
class GameHost : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the GameHost object
     * @param parent The parent object (default is nullptr)
     */
    explicit GameHost(QObject *parent = nullptr);
    /**
     * @brief Destroys the GameHost object
     */
    virtual ~GameHost();

    /**
     * @brief Requests a new game to be started
     * @param mode The play mode for the new game
     */
    void reqNewGame(PlayMode mode);
    /**
     * @brief Requests the current game to be saved
     */
    void reqSaveGame();
    /**
     * @brief Requests the game to be loaded
     */
    void reqLoadGame();
    /**
     * @brief Requests a player's choice of a cell
     * @param cellId The identifier of the chosen cell
     */
    void reqPlayerChoice(int cellId);
    /**
     * @brief Requests a test connection with the game server
     * @param magickNumber The magic number to be used for the test
     */
    void reqTestConnection(int magickNumber);
    /**
     * @brief Checks if serial port is opened
     * @return Returns True if yes
     */
    bool isSerialPortOpen();
    /**
     * @brief Closes opened serial port
     */
    void closeSerialPort();


signals:
    /**
     * @brief Emitted when a new game is started
     * @param mode The play mode of the new game
     */
    void sigGameStart(PlayMode mode);
    /**
     * @brief Emitted when a player makes a choice
     * @param cellId The identifier of the chosen cell
     * @param cellState The state of the chosen cell ('x', 'o', or ' ')
     */
    void sigPlayerChoice(int cellId, char cellState);
    /**
     * @brief Emitted when the game is over
     * @param winner The index of the winning player (0 for 'x', 1 for 'o', 2 for draw)
     */
    void sigGameOver(int winner);
    /**
     * @brief Emitted when the game is loaded
     * @param boardCells The saved game state
     */
    void sigLoadGame(const QString &boardCells);
    /**
     * @brief Emitted when the test connection is completed
     * @param magickNumber The magic number used for the test
     * @param guiPurpose The purpose of the GUI (test-related)
     */
    void sigTestConnection(int magickNumber, const QString &guiPurpose);

private slots:
    /**
     * @brief Handles the incoming data from the serial port
     */
    void onReadyRead();

private:
    /**
     * @brief Detects the host serial port
     * @return True if the serial port is detected, false otherwise
     */
    bool detectHostSerialPort();
    /**
     * @brief Parses the incoming JSON object
     * @param jsonObj The JSON object to be parsed
     */
    void parseJson(const QJsonObject &jsonObj);

    /* Serial Port */
    QSerialPort m_serialPort;
    QByteArray m_inBuffer;
    int m_magickNumber;
    int m_recvMagickNumber;
    QString m_guiPurpose;
};

/**
 * @brief The singleton instance of the GameHost class
 */
typedef Singleton<GameHost> g_GameHost;

#endif // GAMEHOST_H
