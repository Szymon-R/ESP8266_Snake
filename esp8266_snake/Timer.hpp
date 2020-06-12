#ifndef _TIMER_HPP
#define _TIMER_HPP

#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <utility>
#include <cstdio>

class Timer
{
    public:
        Timer(unsigned long timeout = 1000);
        bool TimeoutOccured();
        void RunTimer();
        void ResetTimer();
        bool SetTimeout(unsigned long timeout);
        void StopTimer();
    
    private:
        bool timeoutOccured = false;
        bool isRunning = false;
        unsigned long strartTime = 0U;
        unsigned long timeout;      // Timeout value
};

inline void Timer::RunTimer()
{
    this->ResetTimer();
    this->isRunning =  true;
}

inline void Timer::ResetTimer()
{
    this->timeoutOccured = false;
    this->strartTime =  millis();
}

#endif