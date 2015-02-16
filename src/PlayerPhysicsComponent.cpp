/*******************************************************************//*
 * Implementation of the PlayerPhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2015-02-16
 *********************************************************************/
#include "PlayerPhysicsComponent.h"

#include "GameEntity.h"
#include "GameEntityFactory.h"
#include "RenderComponent.h"
#include "WindowElements.h"

PlayerPhysicsComponent::PlayerPhysicsComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements,
                                            GameEntityFactory* gameEntityFactory)
:   gameEntityFactory(gameEntityFactory),
    render(NULL),
    velocity(0,0),
    velocityPerSecond(500),
    shooting(false)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    render = gameEntity->getRenderComponent();
    health = 4;
    maxHealth = 4;
}

PlayerPhysicsComponent::~PlayerPhysicsComponent()
{
}

void PlayerPhysicsComponent::update()
{
	float timeSinceLastFrame = timeBasedMovementTimer.getTimeOnTimer() / 1000.f;
    gameEntity->position += velocity*timeSinceLastFrame;

    if (gameEntity->position.x > windowElements->WINDOW_WIDTH)
    {
        gameEntity->position.x = windowElements->WINDOW_WIDTH;
    }
    else if (gameEntity->position.x < 0)
    {
        gameEntity->position.x = 0;
    }

    int height = render->getRenderRect().h;
    if (gameEntity->position.y > windowElements->WINDOW_HEIGHT - height/2)
    {
        gameEntity->position.y = windowElements->WINDOW_HEIGHT - height/2;
    }
    else if (gameEntity->position.y < 0 + height/2)
    {
        gameEntity->position.y = 0 + height/2;
    }
    timeBasedMovementTimer.stop();
    timeBasedMovementTimer.start();

    if (shooting)
    {
        if (projectileCapTimer.isStarted())
        {
            if (projectileCapTimer.getTimeOnTimer()>150)
            {
                gameEntityFactory->createPlayerProjectile(gameEntity);
                projectileCapTimer.stop();
            }
        }
        else
        {
            gameEntityFactory->createPlayerProjectile(gameEntity);
        }
        projectileCapTimer.start();
    }
}

void PlayerPhysicsComponent::pauseTimers()
{
    timeBasedMovementTimer.pause();
    projectileCapTimer.pause();
}

void PlayerPhysicsComponent::resumeTimers()
{
    timeBasedMovementTimer.resume();
    projectileCapTimer.resume();
}

void PlayerPhysicsComponent::onHit()
{
    if (!decrementHealth(1))
    {
        onDestroy();
    }
}

void PlayerPhysicsComponent::onDestroy()
{
    gameEntityFactory->createExplosion(gameEntity);
    gameEntity->remove = true;
}
