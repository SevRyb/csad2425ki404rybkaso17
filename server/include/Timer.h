#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>
#include <functional>


class Timer
{
public:
    Timer();
    void update();
    void start();
    void stop();
    void setCallback(std::function<void()> func);

private:
    bool m_isEnabled;

    unsigned long m_interval;
    unsigned long m_prevMillis;
    bool m_isFirstIter;

    std::function<void()> m_callbackFunc;
};

#endif //TIMER_H