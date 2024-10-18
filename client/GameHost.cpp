
#include <QDebug>
#include <QMessageBox>

#include "GameHost.h"


GameHost::GameHost(QObject *parent)
    : QObject{parent}
{
    /* Serial Port */
    if (detectHostSerialPort())
    {
        m_serialPort.setBaudRate(9600);
        m_serialPort.open(QIODevice::ReadWrite);
        if (!m_serialPort.isOpen())
        {
            QMessageBox::critical(NULL, "Error", QString("Couldn't open %1").arg(m_serialPort.portName()));
        }
    }
    else
    {
        QMessageBox::critical(NULL, "Error", "Host device not found!");
    }

    connect(&m_serialPort, &QSerialPort::readyRead, this, &GameHost::onReadyRead);
}

GameHost::~GameHost() {}

bool GameHost::detectHostSerialPort()
{
    const QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &portInfo : ports)
    {
        if (portInfo.productIdentifier() == 29987)
        {
            m_serialPort.setPort(portInfo);
            return true;
        }
    }
    return false;
}

void GameHost::reqMessage(const QString &msg)
{
    QJsonObject request;
    request["msg"] = msg;
    const QByteArray data = QJsonDocument(request).toJson(QJsonDocument::Compact);
    m_serialPort.write(data);
}

void GameHost::onReadyRead()
{
    QByteArray buffer;
    buffer = m_serialPort.readAll();

    qDebug() << buffer;

    QJsonParseError parseError;
    const QJsonDocument jsonDoc = QJsonDocument::fromJson(buffer, &parseError);
    if (parseError.error == QJsonParseError::NoError)
    {
        if (jsonDoc.isObject())
        {
            parseJson(jsonDoc.object());
        }
        else
        {
            qDebug() << "[ERROR] Invalid message";
        }
    }
    else
    {
        qDebug() << "[ERROR] Invalid message";
    }

}

void GameHost::parseJson(const QJsonObject &jsonObj)
{
    const QJsonValue msgValue = jsonObj.value("msg");
    if (msgValue.isString())
    {
        emit sigMessageRecv(msgValue.toString());
    }
}

