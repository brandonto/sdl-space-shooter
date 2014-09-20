/*******************************************************************//*
 * Rectangular collision body.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-18
 * @modified    2014-09-19
 *********************************************************************/
#ifndef SPACESHOOTER_COLLISIONBODYRECTANGLE_
    #define SPACESHOOTER_COLLISIONBODYRECTANGLE_

#include "CollisionBody.h"
#include <vector>
#include <SDL2/SDL.h>
#include "Vector2D.h"

//NOT COMPLETE

class GameEntity;

class CollisionBodyRectangle : public CollisionBody
{
    private:
        const int typeEnum = SHAPE_RECTANGLE;
        std::vector<Vector2D*> points[4];
        Vector2D unitX;
        Vector2D unitY;

    public:
        //Constructor
        CollisionBodyRectangle(GameEntity* gameEntity);

        //Destructor
        ~CollisionBodyRectangle();

        //Methods
        int getType();
        void checkCollision(GameEntity* gameEntity, int flags);
};

#endif
