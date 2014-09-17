/*******************************************************************//*
 * Implementation of the EnemyPhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-17
 * @modified    2014-09-17
 *********************************************************************/
#include "EnemyPhysicsComponent.h"

#include "GameEntity.h"
#include "GameEntityManager.h"
#include "EnemyRenderComponent.h"
#include "WindowElements.h"

EnemyPhysicsComponent::EnemyPhysicsComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements,
                                            GameEntityManager* gameEntityManager)
:   gameEntity(gameEntity), windowElements(windowElements),
    gameEntityManager(gameEntityManager), render(NULL),
    velocity(0, 200), velocityPerSecond(500), shooting(true)
{
    render = dynamic_cast<EnemyRenderComponent*>(gameEntity->getRenderComponent());
}

EnemyPhysicsComponent::~EnemyPhysicsComponent()
{

}

void EnemyPhysicsComponent::update()
{
	float timeSinceLastFrame = timeBasedMovementTimer.getTimeOnTimer() / 1000.f;
    //x = x + speedPerSeconds*secondsSinceLastFrame
    //gameEntity->xPos += (xVel * timeSinceLastFrame);
    gameEntity->position += velocity*timeSinceLastFrame;

    if (!gameEntity->active)
    {
        if (gameEntity->position.x + render->spriteWidth/2 > 0 &&
            gameEntity->position.y + render->spriteHeight/2 > 0 &&
            gameEntity->position.x - render->spriteWidth/2 < windowElements->WINDOW_WIDTH &&
            gameEntity->position.y - render->spriteHeight/2 < windowElements->WINDOW_HEIGHT)
        {
            gameEntity->active = true;
        }
    }
    else
    {
        if (gameEntity->position.x + render->spriteWidth/2 + offScreenBuffer < 0 ||
            gameEntity->position.y + render->spriteHeight/2 + offScreenBuffer < 0 ||
            gameEntity->position.x - render->spriteWidth/2 - offScreenBuffer > windowElements->WINDOW_WIDTH ||
            gameEntity->position.y - render->spriteHeight/2 - offScreenBuffer > windowElements->WINDOW_HEIGHT)
        {
            gameEntity->remove = true;
        }

        if (!gameEntity->remove && shooting)
        {
            if (projectileCapTimer.isStarted())
            {
                if (projectileCapTimer.getTimeOnTimer()>2000)
                {
                    gameEntityManager->createEnemyProjectile(gameEntity);
                    projectileCapTimer.stop();
                }
            }
            else
            {
                gameEntityManager->createEnemyProjectile(gameEntity);
            }
            projectileCapTimer.start();
        }
    }
    timeBasedMovementTimer.stop();
    timeBasedMovementTimer.start();

}

void EnemyPhysicsComponent::pauseTimers()
{
    timeBasedMovementTimer.pause();
    projectileCapTimer.pause();
}

void EnemyPhysicsComponent::resumeTimers()
{
    timeBasedMovementTimer.resume();
    projectileCapTimer.resume();
}
