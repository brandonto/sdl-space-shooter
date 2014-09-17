/*******************************************************************//*
 * Physics component for EnemyProjectile.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-17
 * @modified    2014-09-17
 *********************************************************************/
#ifndef SPACESHOOTER_ENEMYPROJECTILEPHYSICSCOMPONENT_
    #define SPACESHOOTER_ENEMYPROJECTILEPHYSICSCOMPONENT_

#include "PhysicsComponent.h"
#include <SDL2/SDL.h>
#include "Timer.h"
#include "Vector2D.h"

class GameEntity;
class EnemyProjectileRenderComponent;
class WindowElements;

class EnemyProjectilePhysicsComponent : public PhysicsComponent
{
    private:
        GameEntity* gameEntity;
        WindowElements* windowElements;

        EnemyProjectileRenderComponent* render;
        Timer timeBasedMovementTimer;

    public:
        Vector2D velocity;
        int velocityPerSecond;

        //Constructor
        EnemyProjectilePhysicsComponent(GameEntity* gameEntity, WindowElements* windowElements);

        //Destructor
        ~EnemyProjectilePhysicsComponent();

        //Methods
        void update();
        void pauseTimers();
        void resumeTimers();
};

#endif
