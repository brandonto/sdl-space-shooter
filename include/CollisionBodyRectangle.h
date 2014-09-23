/*******************************************************************//*
 * Rectangular collision body.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-18
 * @modified    2014-09-22
 *********************************************************************/
#ifndef SPACESHOOTER_COLLISIONBODYRECTANGLE_
    #define SPACESHOOTER_COLLISIONBODYRECTANGLE_

#include "CollisionBody.h"

//NOT COMPLETE

class CollisionBodyRectangle : public CollisionBody
{
    private:
        const int typeEnum = SHAPE_RECTANGLE;
        std::vector<Vector2D> points;
        Vector2D unitX, unitY;
        Vector2D topLeftVector, topRightVector;
        Vector2D bottomRightVector, bottomLeftVector;

    public:
        //Constructor
        CollisionBodyRectangle(GameEntity* gameEntity);

        //Destructor
        ~CollisionBodyRectangle();

        //Methods
        void update();
        std::vector<Vector2D>* getPoints();
        int getType();
};

#endif
