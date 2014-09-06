/*******************************************************************//*
 * Implementation of the Timer class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2014-09-06
 *********************************************************************/
 #include "Timer.h"

Timer::Timer()
:   startTime(0), tempTime(0), pausedTime(0), started(false), paused(false)
{

}

void Timer::start()
{
    if (!started)
    {
        startTime = SDL_GetTicks();
        tempTime = startTime;
        pausedTime = 0;
        started = true;
        paused = false;
    }
}

void Timer::stop()
{
    if (started)
    {
        startTime = 0;
        tempTime = 0;
        pausedTime = 0;
        started = false;
        paused = false;
    }
}

void Timer::pause()
{
    if (started)
    {
        if (!paused)
        {
            pausedTime = getTimeOnTimer();
            paused = true;
        }
    }
}

void Timer::resume()
{
    if (started)
    {
        if (paused)
        {
            tempTime = SDL_GetTicks() - pausedTime;
            pausedTime = 0;
            paused = false;
        }
    }
}

Uint32 Timer::getTimeOnTimer()
{
    if (started)
    {
        if (paused)
        {
            return pausedTime;
        }
        else
        {
            return SDL_GetTicks() - tempTime;
        }
    }
    else
    {
        return 0;
    }
}

Uint32 Timer::getTimeSinceTimerStarted()
{
    if (started)
    {
        return SDL_GetTicks() - startTime;
    }
}

bool Timer::isStarted()
{
    return started;
}

bool Timer::isPaused()
{
    return paused;
}

