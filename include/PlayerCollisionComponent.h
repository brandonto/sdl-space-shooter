/*******************************************************************//*
 * Collision component for Player.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-18
 * @modified    2014-09-25
 *********************************************************************/
#ifndef SPACESHOOTER_PLAYERCOLLISIONCOMPONENT_
    #define SPACESHOOTER_PLAYERCOLLISIONCOMPONENT_

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

class PlayerCollisionComponent : public CollisionComponent
{
    private:
        CollisionManager* collisionManager;

        PhysicsComponent* physics;
        RenderComponent* render;

    public:
        //Constructor
        PlayerCollisionComponent(GameEntity* gameEntity, WindowElements* windowElements,
                                CollisionManager* collisionManager);

        //Destructor
        ~PlayerCollisionComponent();

        //Methods
        void update();
};

#endif
