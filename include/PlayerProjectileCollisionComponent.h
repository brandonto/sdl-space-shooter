/*******************************************************************//*
 * Collision component for PlayerProjectile.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-22
 * @modified    2014-09-22
 *********************************************************************/
#ifndef SPACESHOOTER_PLAYERPROJECTILECOLLISIONCOMPONENT_
    #define SPACESHOOTER_PLAYERPROJECTILECOLLISIONCOMPONENT_

#include "CollisionComponent.h"
#include <SDL2/SDL.h>
#include "Timer.h"
#include "Vector2D.h"

//NOT COMPLETE

class CollisionManager;
class GameEntity;
class GameEntityManager;
class PlayerProjectilePhysicsComponent;
class PlayerProjectileRenderComponent;

struct WindowElements;

class PlayerProjectileCollisionComponent : public CollisionComponent
{
    private:
        CollisionManager* collisionManager;

        PlayerProjectilePhysicsComponent* physics;
        PlayerProjectileRenderComponent* render;

    public:
        //Constructor
        PlayerProjectileCollisionComponent(GameEntity* gameEntity, WindowElements* windowElements,
                                CollisionManager* collisionManager);

        //Destructor
        ~PlayerProjectileCollisionComponent();

        //Methods
        void update();
};

#endif
