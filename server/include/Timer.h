#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>
#include <functional>

/**
 * @class Timer
 * @brief A simple timer class that can be used to execute a callback function at regular intervals
 */
class Timer
{
public:
    /**
     * @brief Constructs a Timer object
     */
    Timer();
    /**
     * @brief Updates the timer and executes the callback function if the interval has elapsed
     */
    void update();
    /**
     * @brief Starts the timer
     */
    void start();
    /**
     * @brief Stops the timer
     */
    void stop();
    /**
     * @brief Sets the callback function to be executed when the timer interval elapses
     * @param func The callback function
     */
    void setCallback(std::function<void()> func);

private:
    bool m_isEnabled;

    unsigned long m_interval;
    unsigned long m_prevMillis;
    bool m_isFirstIter;

    std::function<void()> m_callbackFunc;
};

#endif //TIMER_H