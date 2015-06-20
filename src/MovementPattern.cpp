/*******************************************************************//*
 * Implementation of the MovementPattern class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-16
 * @modified    2015-02-26
 *********************************************************************/
#include "MovementPattern.h"

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
	#include <SDL2/SDL.h>
#endif

// Constructor
MovementPattern::MovementPattern()
:   currentVelocity(0,150)
{
    timer.start();
}

// Destructor
MovementPattern::~MovementPattern()
{
}

void MovementPattern::setMovementPattern(int patternId)
{
    if (patternId == MOVEMENT_STRAIGHT)
    {
        Vector2D vector(0, 150);
        int time = 6000;
        velocityQueue.push(vector);
        timeQueue.push(time);
    }
    else if (patternId == MOVEMENT_ZIGZAG)
    {
        Vector2D vector1(120, 120);
        Vector2D vector2(-120, 120);
        int time = 1500;
        velocityQueue.push(vector1);
        velocityQueue.push(vector2);
        velocityQueue.push(vector1);
        velocityQueue.push(vector2);
        timeQueue.push(time);
        timeQueue.push(time);
        timeQueue.push(time);
        timeQueue.push(time);
    }
    else if (patternId == MOVEMENT_SWOOPLEFT)
    {
        Vector2D vector1(-400, 100);
        Vector2D vector2(120, 200);
        Vector2D vector3(0, 150);
        int time = 2000;
        velocityQueue.push(vector1);
        velocityQueue.push(vector2);
        velocityQueue.push(vector3);
        timeQueue.push(time);
        timeQueue.push(time);
        timeQueue.push(time);
    }
    else if (patternId == MOVEMENT_SWOOPRIGHT)
    {
        Vector2D vector1(400, 100);
        Vector2D vector2(-120, 200);
        Vector2D vector3(0, 150);
        int time = 2000;
        velocityQueue.push(vector1);
        velocityQueue.push(vector2);
        velocityQueue.push(vector3);
        timeQueue.push(time);
        timeQueue.push(time);
        timeQueue.push(time);
    }
    else if (patternId == MOVEMENT_STRAIGHTSLOW)
    {
        Vector2D vector1(0, 75);
        Vector2D vector2(0, 0);
        int time1 = 4000;
        int time2 = 3000;
        int time3 = 8000;
        velocityQueue.push(vector1);
        velocityQueue.push(vector2);
        velocityQueue.push(vector1);
        timeQueue.push(time1);
        timeQueue.push(time2);
        timeQueue.push(time3);
    }
    else if (patternId == MOVEMENT_BOSS)
    {
        Vector2D vector1(0, 75);
        Vector2D vector2(0, 0);
        Vector2D vector3(-50, -50);
        Vector2D vector4(50, 50);
        Vector2D vector5(50, -50);
        Vector2D vector6(-50, 50);
        Vector2D vector7(0, 200);
        int time1 = 3000;
        int time2 = 5000;
        velocityQueue.push(vector1);
        velocityQueue.push(vector2);
        velocityQueue.push(vector3);
        velocityQueue.push(vector4);
        velocityQueue.push(vector5);
        velocityQueue.push(vector6);
        velocityQueue.push(vector2);
        velocityQueue.push(vector3);
        velocityQueue.push(vector4);
        velocityQueue.push(vector5);
        velocityQueue.push(vector6);
        velocityQueue.push(vector2);
        velocityQueue.push(vector3);
        velocityQueue.push(vector4);
        velocityQueue.push(vector5);
        velocityQueue.push(vector6);
        velocityQueue.push(vector2);
        velocityQueue.push(vector3);
        velocityQueue.push(vector4);
        velocityQueue.push(vector5);
        velocityQueue.push(vector6);
        velocityQueue.push(vector2);
        velocityQueue.push(vector3);
        velocityQueue.push(vector4);
        velocityQueue.push(vector5);
        velocityQueue.push(vector6);
        velocityQueue.push(vector2);
        velocityQueue.push(vector7);
        timeQueue.push(time1);
        timeQueue.push(time2);
        timeQueue.push(time1);
        timeQueue.push(time1);
        timeQueue.push(time1);
        timeQueue.push(time1);
        timeQueue.push(time2);
        timeQueue.push(time1);
        timeQueue.push(time1);
        timeQueue.push(time1);
        timeQueue.push(time1);
        timeQueue.push(time2);
        timeQueue.push(time1);
        timeQueue.push(time1);
        timeQueue.push(time1);
        timeQueue.push(time1);
        timeQueue.push(time2);
        timeQueue.push(time1);
        timeQueue.push(time1);
        timeQueue.push(time1);
        timeQueue.push(time1);
        timeQueue.push(time2);
        timeQueue.push(time1);
        timeQueue.push(time1);
        timeQueue.push(time1);
        timeQueue.push(time1);
        timeQueue.push(time2);
        timeQueue.push(time2);
    }

    currentVelocity = velocityQueue.front();
    currentVelocityTime = timeQueue.front();
    velocityQueue.pop();
    timeQueue.pop();
    timer.stop();
    timer.start();
}

Vector2D MovementPattern::getCurrentVelocity()
{
    if (timer.getTimeOnTimer() > currentVelocityTime)
    {
        if (!velocityQueue.empty())
        {
            currentVelocity = velocityQueue.front();
            currentVelocityTime = timeQueue.front();
            velocityQueue.pop();
            timeQueue.pop();
            timer.stop();
            timer.start();
        }
    }
    return currentVelocity;
}

void MovementPattern::pauseTimers()
{
    timer.pause();
}

void MovementPattern::resumeTimers()
{
    timer.resume();
}
