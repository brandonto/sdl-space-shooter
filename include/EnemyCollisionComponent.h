/*******************************************************************//*
 * Collision component for Enemy.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-22
 * @modified    2014-09-22
 *********************************************************************/
#ifndef SPACESHOOTER_ENEMYCOLLISIONCOMPONENT_
    #define SPACESHOOTER_ENEMYCOLLISIONCOMPONENT_

#include "CollisionComponent.h"
#include <SDL2/SDL.h>
#include "Timer.h"
#include "Vector2D.h"

//NOT COMPLETE

class CollisionManager;
class GameEntity;
class GameEntityManager;
class EnemyPhysicsComponent;
class EnemyRenderComponent;

struct WindowElements;

class EnemyCollisionComponent : public CollisionComponent
{
    private:
        CollisionManager* collisionManager;

        EnemyPhysicsComponent* physics;
        EnemyRenderComponent* render;

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
