
#include <QDebug>
#include <QMessageBox>

#include "GameHost.h"


GameHost::GameHost(QObject *parent)
    : QObject{parent}
    , m_magickNumber{0}
{
    /* Serial Port */
    if (detectHostSerialPort())
    {
        m_serialPort.setBaudRate(9600);
        m_serialPort.open(QIODevice::ReadWrite);
        if (!m_serialPort.isOpen())
        {
            //QMessageBox::critical(NULL, "Error", QString("Couldn't open %1").arg(m_serialPort.portName()));
            qDebug() << QString("Couldn't open %1").arg(m_serialPort.portName());
        }
    }
    else
    {
        //QMessageBox::critical(NULL, "Error", "Host device not found!");
        qDebug() << "Host device not found!";
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

void GameHost::reqNewGame(PlayMode mode)
{
    qDebug() << "reqNewGame, mode: " << static_cast<int>(mode);
    QJsonObject request;
    request["type"] = static_cast<int>(JsonType::New_Game);
    request["mode"] = static_cast<int>(mode);
    const QByteArray data = QJsonDocument(request).toJson(QJsonDocument::Compact);
    m_serialPort.write(data);
}

void GameHost::reqSaveGame()
{
    qDebug() << "reqSaveGame";
    QJsonObject request;
    request["type"] = static_cast<int>(JsonType::Save_Game);
    const QByteArray data = QJsonDocument(request).toJson(QJsonDocument::Compact);
    m_serialPort.write(data);
}

void GameHost::reqLoadGame()
{
    qDebug() << "reqLoadGame";
    QJsonObject request;
    request["type"] = static_cast<int>(JsonType::Load_Game);
    const QByteArray data = QJsonDocument(request).toJson(QJsonDocument::Compact);
    m_serialPort.write(data);
}

void GameHost::reqPlayerChoice(int cellId)
{
    qDebug() << "reqPlayerChoice, cellId: " << cellId;
    QJsonObject request;
    request["type"] = static_cast<int>(JsonType::Player_Choice);
    request["cell"] = cellId;
    const QByteArray data = QJsonDocument(request).toJson(QJsonDocument::Compact);
    m_serialPort.write(data);
}

void GameHost::reqTestConnection(int magickNumber)
{
    qDebug() << "reqTestConnection, magickNumber: " << magickNumber;
    QJsonObject request;
    request["type"] = static_cast<int>(JsonType::Test);
    request["mn"] = magickNumber;
    const QByteArray data = QJsonDocument(request).toJson(QJsonDocument::Compact);
    m_serialPort.write(data);
}

void GameHost::onReadyRead()
{
    bool endOfPacket = false;
    const QByteArray buffer = m_serialPort.readAll();
    const int closeBracketPos = buffer.indexOf('}');

    if (closeBracketPos >= 0)
    {
        m_inBuffer.append(buffer.left(closeBracketPos + 1));
        endOfPacket = true;
    }
    else
    {
        m_inBuffer.append(buffer);
    }

    if (endOfPacket)
    {
        qDebug() << "[INFO] Message len: " << m_inBuffer.length();
        qDebug() << m_inBuffer;

        QJsonParseError parseError;
        const QJsonDocument jsonDoc = QJsonDocument::fromJson(m_inBuffer, &parseError);
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
        m_inBuffer.clear();
        m_inBuffer.append(buffer.mid(closeBracketPos + 1));
    }
}

void GameHost::parseJson(const QJsonObject &jsonObj)
{
    const QJsonValue typeValue = jsonObj.value("type");
    if (!typeValue.isNull())
    {
        const JsonType type = static_cast<JsonType>(typeValue.toInt());
        switch (type)
        {
        case JsonType::New_Game:
        {
            if (!jsonObj.contains("mode"))
                break;

            const QJsonValue modeValue = jsonObj.value("mode");
            if (!modeValue.isNull())
            {
                const PlayMode mode = static_cast<PlayMode>(modeValue.toInt());
                emit sigGameStart(mode);
            }
            break;
        }
        case JsonType::Player_Choice:
        {
            if (!jsonObj.contains("cell") || !jsonObj.contains("state"))
                break;

            const QJsonValue cellValue = jsonObj.value("cell");
            const QJsonValue stateValue = jsonObj.value("state");
            if (!cellValue.isNull() && !stateValue.isNull() && stateValue.isString())
            {
                const int cellId = cellValue.toInt();
                const char state = stateValue.toString().at(0).toLatin1();
                emit sigPlayerChoice(cellId, state);
            }
            break;
        }
        case JsonType::Game_Over:
        {
            if (!jsonObj.contains("win"))
                break;

            const QJsonValue winnerValue = jsonObj.value("win");
            if (!winnerValue.isNull())
            {
                emit sigGameOver(winnerValue.toInt());
            }
            break;
        }
        case JsonType::Load_Game:
        {
            if (!jsonObj.contains("#"))
                break;

            const QJsonValue boardCellsValue = jsonObj.value("#");
            if (!boardCellsValue.isNull() && boardCellsValue.isString())
            {
                emit sigLoadGame(boardCellsValue.toString());
            }
            break;
        }
        case JsonType::Test:
        {
            if (!jsonObj.contains("mn") || !jsonObj.contains("gui"))
                break;
            const QJsonValue magickNumberValue = jsonObj.value("mn");
            const QJsonValue guiValue = jsonObj.value("gui");
            emit sigTestConnection(magickNumberValue.toInt(), guiValue.toString());
            break;
        }
        default:
            break;
        }
    }
}

