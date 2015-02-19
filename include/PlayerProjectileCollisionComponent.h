/*******************************************************************//*
 * Collision component for PlayerProjectile.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-22
 * @modified    2015-02-19
 *********************************************************************/
#ifndef SPACESHOOTER_PLAYERPROJECTILECOLLISIONCOMPONENT_
    #define SPACESHOOTER_PLAYERPROJECTILECOLLISIONCOMPONENT_

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

class PlayerProjectileCollisionComponent : public CollisionComponent
{
    private:
        CollisionManager* collisionManager;

        PhysicsComponent* physics;
        RenderComponent* render;

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
