/*******************************************************************//*
 * Physics component for PlayerProjectile.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-08
 * @modified    2014-09-08
 *********************************************************************/
#ifndef SPACESHOOTER_PLAYERPROJECTILEPHYSICSCOMPONENT_
    #define SPACESHOOTER_PLAYERPROJECTILEPHYSICSCOMPONENT_

#include "PhysicsComponent.h"
#include <SDL2/SDL.h>
#include "Timer.h"

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
        float xVel, yVel;
        int velocityPerSecond;

        //Constructor
        PlayerProjectilePhysicsComponent(GameEntity* gameEntity, WindowElements* windowElements);

        //Destructor
        ~PlayerProjectilePhysicsComponent();

        //Methods
        void update();
};

#endif
