/*******************************************************************//*
 * Physics component for Player.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2014-09-09
 *********************************************************************/
#ifndef SPACESHOOTER_PLAYERPHYSICSCOMPONENT_
    #define SPACESHOOTER_PLAYERPHYSICSCOMPONENT_

#include "PhysicsComponent.h"
#include <SDL2/SDL.h>
#include "Timer.h"

class GameEntity;
class GameEntityManager;
class PlayerRenderComponent;
class WindowElements;

class PlayerPhysicsComponent : public PhysicsComponent
{
    private:
        GameEntity* gameEntity;
        WindowElements* windowElements;
        GameEntityManager* gameEntityManager;

        PlayerRenderComponent* render;
        Timer timeBasedMovementTimer;
        Timer projectileCapTimer;

    public:
        float xVel, yVel;
        int velocityPerSecond;
        bool shooting;

        //Constructor
        PlayerPhysicsComponent(GameEntity* gameEntity, WindowElements* windowElements,
                                GameEntityManager* gameEntityManager);

        //Destructor
        ~PlayerPhysicsComponent();

        //Methods
        void update();
};

#endif
