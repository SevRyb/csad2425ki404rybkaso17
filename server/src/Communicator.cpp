#include "Communicator.h"


Communicator::Communicator() {}

void Communicator::notifyMessageEdited(String msg)
{
        JsonDocument jsonDoc;
        jsonDoc["msg"] = msg;
        sendJson(jsonDoc);
}

void Communicator::sendJson(const JsonDocument& jsonDoc)
{
    serializeJson(jsonDoc, Serial);
}

void Communicator::processJson()
{
    if (incomingJsonDoc["msg"].is<String>())
    {
        String msg = incomingJsonDoc["msg"].as<String>();
        msg = "Message: " + msg;
        notifyMessageEdited(msg);
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
