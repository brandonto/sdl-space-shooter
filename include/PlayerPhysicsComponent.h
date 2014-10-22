/*******************************************************************//*
 * Physics component for Player.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2014-10-21
 *********************************************************************/
#ifndef SPACESHOOTER_PLAYERPHYSICSCOMPONENT_
    #define SPACESHOOTER_PLAYERPHYSICSCOMPONENT_

#include "PhysicsComponent.h"
#include <SDL2/SDL.h>
#include "Timer.h"
#include "Vector2D.h"

class GameEntity;
class GameEntityManager;
class RenderComponent;

struct WindowElements;

class PlayerPhysicsComponent : public PhysicsComponent
{
    private:
        GameEntityManager* gameEntityManager;

        RenderComponent* render;
        Timer timeBasedMovementTimer;
        Timer projectileCapTimer;

    public:
        Vector2D velocity;
        int velocityPerSecond;
        bool shooting;

        //Constructor
        PlayerPhysicsComponent(GameEntity* gameEntity, WindowElements* windowElements,
                                GameEntityManager* gameEntityManager);

        //Destructor
        ~PlayerPhysicsComponent();

        //Methods
        void update();
        void pauseTimers();
        void resumeTimers();
        void onDestroy();
};

#endif
