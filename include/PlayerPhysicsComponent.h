/*******************************************************************//*
 * Physics component for Player.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2014-09-06
 *********************************************************************/
#ifndef SPACESHOOTER_PLAYERPHYSICSCOMPONENT_
    #define SPACESHOOTER_PLAYERPHYSICSCOMPONENT_

#include "PhysicsComponent.h"
#include <SDL2/SDL.h>
#include "Timer.h"

class GameEntity;
class PlayerRenderComponent;
class WindowElements;

class PlayerPhysicsComponent : public PhysicsComponent
{
    private:
        GameEntity* gameEntity;
        WindowElements* windowElements;

        PlayerRenderComponent* render;
        Timer timeBasedMovementTimer;

    public:
        float xVel, yVel;
        int velocityPerSecond;

        //Constructor
        PlayerPhysicsComponent(GameEntity* gameEntity, WindowElements* windowElements);

        //Destructor
        ~PlayerPhysicsComponent();

        //Methods
        void update();
};

#endif
