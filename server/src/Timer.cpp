#include "Timer.h"


Timer::Timer()
{
    m_isEnabled = false;
    m_interval = 800;
    m_prevMillis = 0;
    m_isFirstIter = true;
}

void Timer::update()
{
    if (!m_isEnabled)
        return;
    unsigned long currentMillis = millis();
    if (currentMillis - m_prevMillis >= m_interval)
    {
        m_prevMillis = currentMillis;
        if (!m_isFirstIter)
            m_callbackFunc();
        m_isFirstIter = false;
    }
}

void Timer::start()
{
    m_isEnabled = true;
    m_prevMillis = 0;
    m_isFirstIter = true;
}

void Timer::stop()
{
    m_isEnabled = false;
}

void Timer::setCallback(std::function<void()> func)
{
    m_callbackFunc = func;
}

