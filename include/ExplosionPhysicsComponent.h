/*******************************************************************//*
 * Physics component for Explosion.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-25
 * @modified    2014-09-25
 *********************************************************************/
#ifndef SPACESHOOTER_EXPLOSIONPHYSICSCOMPONENT_
    #define SPACESHOOTER_EXPLOSIONPHYSICSCOMPONENT_

#include "PhysicsComponent.h"
#include <SDL2/SDL.h>
#include "Timer.h"
#include "Vector2D.h"

class GameEntity;
class RenderComponent;

struct WindowElements;

class ExplosionPhysicsComponent : public PhysicsComponent
{
    private:
        RenderComponent* render;
        Timer durationTimer;

    public:
        Vector2D velocity;

        //Constructor
        ExplosionPhysicsComponent(GameEntity* gameEntity, WindowElements* windowElements);

        //Destructor
        ~ExplosionPhysicsComponent();

        //Methods
        void update();
        void pauseTimers();
        void resumeTimers();
};

#endif
