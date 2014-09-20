/*******************************************************************//*
 * Interface containing methods that all collision components must
 * implement
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-19
 * @modified    2014-09-19
 *********************************************************************/
#ifndef SPACESHOOTER_COLLISIONCOMPONENT_
    #define SPACESHOOTER_COLLISIONCOMPONENT_

class CollisionBody;
class GameEntity;

struct WindowElements;

class CollisionComponent
{
    public:
        //Fields
        GameEntity* gameEntity;
        WindowElements* windowElements;
        CollisionBody* body;

        //Destructor
        virtual ~CollisionComponent(){};

        //Methods
        virtual void update() = 0;
};

#endif

