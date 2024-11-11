
#ifndef GAMEHOST_H
#define GAMEHOST_H


#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "Singleton.h"


enum class PlayMode {Man_AI, Man_Man, AI_AI};
enum class JsonType {Test = -1, New_Game, Player_Choice, Game_Over, Load_Game, Save_Game};


class GameHost : public QObject
{
    Q_OBJECT
public:
    explicit GameHost(QObject *parent = nullptr);
    virtual ~GameHost();

    void reqNewGame(PlayMode mode);
    void reqSaveGame();
    void reqLoadGame();
    void reqPlayerChoice(int cellId);

    void reqTestConnection(int magickNumber);


signals:
    void sigGameStart(PlayMode mode);
    void sigPlayerChoice(int cellId, unsigned char cellState);
    void sigGameOver(int winner);
    void sigLoadGame(const QString &boardCells);

    void sigTestConnection(int magickNumber, const QString &guiPurpose);

private slots:
    void onReadyRead();

private:
    bool detectHostSerialPort();
    void parseJson(const QJsonObject &jsonObj);
    /* Serial Port */
    QSerialPort m_serialPort;
    QByteArray m_inBuffer;
    int m_magickNumber;
    int m_recvMagickNumber;
    QString m_guiPurpose;
};

typedef Singleton<GameHost> g_GameHost;

#endif // GAMEHOST_H
