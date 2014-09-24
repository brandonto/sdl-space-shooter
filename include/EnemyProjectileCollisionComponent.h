/*******************************************************************//*
 * Collision component for EnemyProjectile.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-22
 * @modified    2014-09-22
 *********************************************************************/
#ifndef SPACESHOOTER_ENEMYPROJECTILECOLLISIONCOMPONENT_
    #define SPACESHOOTER_ENEMYPROJECTILECOLLISIONCOMPONENT_

#include "CollisionComponent.h"
#include <SDL2/SDL.h>
#include "Timer.h"
#include "Vector2D.h"

//NOT COMPLETE

class CollisionManager;
class GameEntity;
class GameEntityManager;
class EnemyProjectilePhysicsComponent;
class EnemyProjectileRenderComponent;

struct WindowElements;

class EnemyProjectileCollisionComponent : public CollisionComponent
{
    private:
        CollisionManager* collisionManager;

        EnemyProjectilePhysicsComponent* physics;
        EnemyProjectileRenderComponent* render;

    public:
        //Constructor
        EnemyProjectileCollisionComponent(GameEntity* gameEntity, WindowElements* windowElements,
                                CollisionManager* collisionManager);

        //Destructor
        ~EnemyProjectileCollisionComponent();

        //Methods
        void update();
};

#endif
