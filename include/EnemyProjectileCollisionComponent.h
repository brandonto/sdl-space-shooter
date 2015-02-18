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
#ifdef _WIN32
	#include <SDL.h>
#endif
#ifdef linux
	#include <SDL2/SDL.h>
#endif

#include "Timer.h"
#include "Vector2D.h"

//NOT COMPLETE

class CollisionManager;
class GameEntity;
class GameEntityManager;
class PhysicsComponent;
class RenderComponent;

struct WindowElements;

class EnemyProjectileCollisionComponent : public CollisionComponent
{
    private:
        CollisionManager* collisionManager;

        PhysicsComponent* physics;
        RenderComponent* render;

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
