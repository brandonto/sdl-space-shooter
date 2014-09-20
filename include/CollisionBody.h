/*******************************************************************//*
 * This class defines the shape of the collidable body .
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-18
 * @modified    2014-09-18
 *********************************************************************/
#ifndef SPACESHOOTER_COLLISIONBODY_
    #define SPACESHOOTER_COLLISIONBODY_

#include <SDL2/SDL.h>
#include "GameEntity.h"
#include "Vector2D.h"

//NOT COMPLETE

class CollisionBody
{
    private:

    public:
        //Destructor
        ~CollisionBody(){};

        //Methods
        virtual int getType() = 0;

    protected:
        GameEntity* gameEntity;
};

enum CollisionBodyShape
{
    SHAPE_CIRCLE,
    SHAPE_RECTANGLE,
    SHAPE_POLYGON,
};

#endif
