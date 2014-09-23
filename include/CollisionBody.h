/*******************************************************************//*
 * This class defines the shape of the collidable body .
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-18
 * @modified    2014-09-22
 *********************************************************************/
#ifndef SPACESHOOTER_COLLISIONBODY_
    #define SPACESHOOTER_COLLISIONBODY_

#include <vector>
#include <SDL2/SDL.h>
#include "Vector2D.h"

class GameEntity;
class RenderComponent;

class CollisionBody
{
    private:

    public:
        SDL_Rect boundingRect;

        //Destructor
        ~CollisionBody(){};

        //Methods
        virtual void update() = 0;
        virtual std::vector<Vector2D>* getPoints() = 0;
        virtual int getType() = 0;
        //virtual CollisionBodyRectangle* getBoundingRectangle();

    protected:
        GameEntity* gameEntity;
        RenderComponent* render;
};

enum CollisionBodyShape
{
    SHAPE_CIRCLE,
    SHAPE_RECTANGLE,
    SHAPE_POLYGON,
};

#endif
