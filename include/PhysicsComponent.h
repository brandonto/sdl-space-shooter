/*******************************************************************//*
 * Interface containing one method that all physics components must
 * implement
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2014-09-15
 *********************************************************************/
#ifndef SPACESHOOTER_PHYSICSCOMPONENT_
    #define SPACESHOOTER_PHYSICSCOMPONENT_

class PhysicsComponent
{
    public:
        //Destructor
        virtual ~PhysicsComponent(){};

        //Methods
        virtual void update() = 0;
        virtual void pauseTimers(){};
        virtual void resumeTimers(){};
};

#endif
