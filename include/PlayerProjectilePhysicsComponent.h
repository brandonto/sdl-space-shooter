/*******************************************************************//*
 * Physics component for PlayerProjectile.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-08
 * @modified    2014-09-15
 *********************************************************************/
#ifndef SPACESHOOTER_PLAYERPROJECTILEPHYSICSCOMPONENT_
    #define SPACESHOOTER_PLAYERPROJECTILEPHYSICSCOMPONENT_

#include "PhysicsComponent.h"
#include <SDL2/SDL.h>
#include "Timer.h"
#include "Vector2D.h"

class GameEntity;
class PlayerProjectileRenderComponent;
class WindowElements;

class PlayerProjectilePhysicsComponent : public PhysicsComponent
{
    private:
        GameEntity* gameEntity;
        WindowElements* windowElements;

        PlayerProjectileRenderComponent* render;
        Timer timeBasedMovementTimer;

    public:
        Vector2D velocity;
        int velocityPerSecond;

        //Constructor
        PlayerProjectilePhysicsComponent(GameEntity* gameEntity, WindowElements* windowElements);

        //Destructor
        ~PlayerProjectilePhysicsComponent();

        //Methods
        void update();
        void pauseTimers();
        void resumeTimers();
};

#endif
