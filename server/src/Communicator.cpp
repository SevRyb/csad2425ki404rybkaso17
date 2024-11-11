#include "Communicator.h"


Communicator::Communicator(Game* game)
    : m_game(game)
{
}

void Communicator::notifyGameStarted(PlayMode mode)
{
        JsonDocument jsonDoc;
        jsonDoc["type"] = static_cast<int>(JsonType::New_Game);
        jsonDoc["mode"] = static_cast<int>(mode);
        sendJson(jsonDoc);
}

void Communicator::notifyPlayerChoice(int cellId, char state)
{
        JsonDocument jsonDoc;
        jsonDoc["type"] = static_cast<int>(JsonType::Player_Choice);
        jsonDoc["cell"] = cellId;
        char s[] = {state, '\0'};
        jsonDoc["state"] = s;
        sendJson(jsonDoc);
}

void Communicator::notifyGameOver(int winner)
{
        JsonDocument jsonDoc;
        jsonDoc["type"] = static_cast<int>(JsonType::Game_Over);
        jsonDoc["win"] = winner;
        sendJson(jsonDoc);
}

void Communicator::notifyGameLoaded(char cells[9])
{
    JsonDocument jsonDoc;
    jsonDoc["type"] = static_cast<int>(JsonType::Load_Game);
    char s[10];
    memcpy(s, cells, 9);
    s[9] = '\0';
    jsonDoc["#"] = s;
    sendJson(jsonDoc);
}

void Communicator::sendJson(const JsonDocument& jsonDoc)
{
    serializeJson(jsonDoc, Serial);
}

void Communicator::processJson()
{
    if (incomingJsonDoc["type"].is<int>())
    {
        JsonType jsonType = static_cast<JsonType>(incomingJsonDoc["type"].as<int>());
        switch (jsonType)
        {
        case JsonType::New_Game:
        {
            if (incomingJsonDoc["mode"].is<int>())
            {
                PlayMode playMode = static_cast<PlayMode>(incomingJsonDoc["mode"].as<int>());
                m_game->onNew(playMode);
            }
            break;
        }
        case JsonType::Player_Choice:
        {
            if (incomingJsonDoc["cell"].is<int>())
            {
                int cellId = incomingJsonDoc["cell"].as<int>();
                m_game->onPlayerChoice(cellId);
            }
            break;
        }
        case JsonType::Save_Game:
        {
            m_game->onSave();
            break;
        }
        case JsonType::Load_Game:
        {
            m_game->onLoad();
            break;
        }
        case JsonType::Test:
        {
            if (incomingJsonDoc["mn"].is<int>())
            {
                onTestConnection(incomingJsonDoc["mn"].as<int>());
            }
            break;
        }
        default:
            break;
        }
    }
}

void Communicator::handleSerialData()
{
    while (Serial.available())
    {
        DeserializationError error = deserializeJson(incomingJsonDoc, Serial);
        if (error) 
        {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.c_str());
            return;
        }
        processJson();
    }
}

void Communicator::onTestConnection(int magickNumber)
{
    JsonDocument jsonDoc;
    jsonDoc["type"] = static_cast<int>(JsonType::Test);
    jsonDoc["mn"] = magickNumber * 2 + 123;
    char guiPurpose[] = "TicTacToe#3x3";
    jsonDoc["gui"] = guiPurpose;
    sendJson(jsonDoc);
}
