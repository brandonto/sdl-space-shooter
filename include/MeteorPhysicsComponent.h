/*******************************************************************//*
 * Physics component for Meteor.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-14
 * @modified    2014-09-25
 *********************************************************************/
#ifndef SPACESHOOTER_METEORPHYSICSCOMPONENT_
    #define SPACESHOOTER_METEORPHYSICSCOMPONENT_

#include "PhysicsComponent.h"
#ifdef _WIN32
	#include <SDL.h>
#endif
#ifdef linux
	#include <SDL2/SDL.h>
#endif

#include "Timer.h"
#include "Vector2D.h"

class GameEntity;
class GameEntityManager;
class RenderComponent;

struct WindowElements;

class MeteorPhysicsComponent : public PhysicsComponent
{
    private:
        GameEntityManager* gameEntityManager;

        RenderComponent* render;
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
