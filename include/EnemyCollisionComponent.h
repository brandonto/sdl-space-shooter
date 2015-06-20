/*******************************************************************//*
 * Collision component for Enemy.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-22
 * @modified    2014-09-25
 *********************************************************************/
#ifndef SPACESHOOTER_ENEMYCOLLISIONCOMPONENT_
    #define SPACESHOOTER_ENEMYCOLLISIONCOMPONENT_

#include "CollisionComponent.h"

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
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

class EnemyCollisionComponent : public CollisionComponent
{
    private:
        CollisionManager* collisionManager;

        PhysicsComponent* physics;
        RenderComponent* render;

    public:
        //Constructor
        EnemyCollisionComponent(GameEntity* gameEntity, WindowElements* windowElements,
                                CollisionManager* collisionManager);

        //Destructor
        ~EnemyCollisionComponent();

        //Methods
        void update();
};

#endif
