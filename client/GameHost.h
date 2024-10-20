
#ifndef GAMEHOST_H
#define GAMEHOST_H


#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "Singleton.h"



class GameHost : public QObject
{
    Q_OBJECT
public:
    explicit GameHost(QObject *parent = nullptr);
    virtual ~GameHost();

    void reqMessage(const QString &msg);
    QString parseJson(const QJsonObject &jsonObj);

signals:
    void sigMessageRecv(QString msg);

private slots:
    void onReadyRead();

private:
    bool detectHostSerialPort();

    /* Serial Port */
    QSerialPort m_serialPort;
};

typedef Singleton<GameHost> g_GameHost;

#endif // GAMEHOST_H
