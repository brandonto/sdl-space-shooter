/*******************************************************************//*
 * Core MovementPattern class. Initializes and closes SDL and contains the
 * main game loop.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-16
 * @modified    2015-02-17
 *********************************************************************/
#ifndef SPACESHOOTER_MOVEMENTPATTERN_H_
    #define SPACESHOOTER_MOVEMENTPATTERN_H_

#include <queue>
#include <utility>

#include "Timer.h"
#include "Vector2D.h"

class MovementPattern
{
    private:
        //Fields
        Timer timer;
        std::queue<Vector2D> velocityQueue;
        std::queue<int> timeQueue;
        Vector2D currentVelocity;
        int currentVelocityTime;

    public:
        //Constructor
        MovementPattern();

        //Destructor
        ~MovementPattern();

        //Methods
        void setMovementPattern(int patternId);
        Vector2D getCurrentVelocity();
};

enum MovementPatternEnum
{
    MOVEMENT_STRAIGHT,
    MOVEMENT_ZIGZAG,
    MOVEMENT_SWOOPLEFT,
    MOVEMENT_SWOOPRIGHT,
    MOVEMENT_STRAIGHTSLOW,
};

#endif

