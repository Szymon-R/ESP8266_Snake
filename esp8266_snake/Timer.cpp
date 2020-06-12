#include "Timer.hpp"

Timer::Timer(unsigned long timeout) : timeout(timeout)
{

}

bool Timer::SetTimeout(unsigned long timeout)
{
    if (this->isRunning)
    {
        return false;
    }

    this->timeout = timeout;
    return true;
}

void Timer::StopTimer()
{
    this->isRunning =  false;
    this->timeoutOccured = false;
} 

 bool Timer::TimeoutOccured()
 {
    if (this->timeoutOccured)
    {
        return true;
    }

    if (this->isRunning && ((millis() - this->strartTime) > this->timeout))
    {
        this->timeoutOccured = true;
        return true;
    }
    else
    {
        this->timeoutOccured = false;
        return false;
    }
 }