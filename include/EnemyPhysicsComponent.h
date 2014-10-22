/*******************************************************************//*
 * Physics component for Enemy.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-17
 * @modified    2014-10-21
 *********************************************************************/
#ifndef SPACESHOOTER_ENEMYPHYSICSCOMPONENT_
    #define SPACESHOOTER_ENEMYPHYSICSCOMPONENT_

#include "PhysicsComponent.h"
#include <SDL2/SDL.h>
#include "Timer.h"
#include "Vector2D.h"

class GameEntity;
class GameEntityManager;
class RenderComponent;

struct WindowElements;

class EnemyPhysicsComponent : public PhysicsComponent
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
        const int offScreenBuffer = 25;

        //Constructor
        EnemyPhysicsComponent(GameEntity* gameEntity, WindowElements* windowElements,
                                GameEntityManager* gameEntityManager);

        //Destructor
        ~EnemyPhysicsComponent();

        //Methods
        void update();
        void pauseTimers();
        void resumeTimers();
        void onDestroy();
};

#endif
