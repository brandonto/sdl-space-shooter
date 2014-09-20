/*******************************************************************//*
 * Physics component for Meteor.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-14
 * @modified    2014-09-19
 *********************************************************************/
#ifndef SPACESHOOTER_METEORPHYSICSCOMPONENT_
    #define SPACESHOOTER_METEORPHYSICSCOMPONENT_

#include "PhysicsComponent.h"
#include <SDL2/SDL.h>
#include "Timer.h"
#include "Vector2D.h"

class GameEntity;
class GameEntityManager;
class MeteorRenderComponent;

struct WindowElements;

class MeteorPhysicsComponent : public PhysicsComponent
{
    private:
        GameEntityManager* gameEntityManager;

        MeteorRenderComponent* render;
        Timer timeBasedMovementTimer;
        Timer projectileCapTimer;

        int angleIncrementCounter;
        int angleIncrementModulus;
        const int offScreenBuffer = 25;

    public:
        Vector2D velocity;
        int velocityPerSecond;

        //Constructor
        MeteorPhysicsComponent(GameEntity* gameEntity, WindowElements* windowElements);

        //Destructor
        ~MeteorPhysicsComponent();

        //Methods
        void update();
        void pauseTimers();
        void resumeTimers();
};

#endif
