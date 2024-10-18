#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <Arduino.h>
#include <ArduinoJson.h>


class Communicator
{
public:
    Communicator();
    void notifyMessageEdited(String msg);
    void sendJson(const JsonDocument& jsonDoc);
    void processJson();
    void handleSerialData();

private:
    JsonDocument incomingJsonDoc;
};

#endif //COMMUNICATOR_H