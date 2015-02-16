/*******************************************************************//*
 * Implementation of the EnemyPhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-17
 * @modified    2015-02-16
 *********************************************************************/
#include "EnemyPhysicsComponent.h"

#include "GameEntity.h"
#include "GameEntityFactory.h"
#include "RenderComponent.h"
#include "WindowElements.h"

EnemyPhysicsComponent::EnemyPhysicsComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements,
                                            GameEntityFactory* gameEntityFactory)
:   gameEntityFactory(gameEntityFactory),
    render(NULL),
    velocity(0,200),
    velocityPerSecond(500),
    shooting(true)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    render = gameEntity->getRenderComponent();
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

    int spriteWidth = render->getTexture()->getSpriteWidth();
    int spriteHeight = render->getTexture()->getSpriteHeight();

    if (!gameEntity->active)
    {
        if (gameEntity->position.x + spriteWidth/2 > 0 &&
            gameEntity->position.y + spriteHeight/2 > 0 &&
            gameEntity->position.x - spriteWidth/2 < windowElements->WINDOW_WIDTH &&
            gameEntity->position.y - spriteHeight/2 < windowElements->WINDOW_HEIGHT)
        {
            gameEntity->active = true;
        }
    }
    else
    {
        if (gameEntity->position.x + spriteWidth/2 + offScreenBuffer < 0 ||
            gameEntity->position.y + spriteHeight/2 + offScreenBuffer < 0 ||
            gameEntity->position.x - spriteWidth/2 - offScreenBuffer > windowElements->WINDOW_WIDTH ||
            gameEntity->position.y - spriteHeight/2 - offScreenBuffer > windowElements->WINDOW_HEIGHT)
        {
            gameEntity->remove = true;
        }

        if (!gameEntity->remove && shooting)
        {
            if (projectileCapTimer.isStarted())
            {
                if (projectileCapTimer.getTimeOnTimer()>2000)
                {
                    gameEntityFactory->createEnemyProjectile(gameEntity);
                    projectileCapTimer.stop();
                }
            }
            else
            {
                gameEntityFactory->createEnemyProjectile(gameEntity);
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

void EnemyPhysicsComponent::onHit()
{
    onDestroy();
}

void EnemyPhysicsComponent::onDestroy()
{
    gameEntityFactory->createExplosion(gameEntity);
    gameEntity->remove = true;
}
