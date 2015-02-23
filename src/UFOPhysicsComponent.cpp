/*******************************************************************//*
 * Implementation of the UFOPhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-23
 * @modified    2015-02-23
 *********************************************************************/
#include "UFOPhysicsComponent.h"

#include <cmath>

#include "GameEntity.h"
#include "GameEntityFactory.h"
#include "GameState.h" // Observing
#include "Level.h" // For SpawnData struct
#include "RenderComponent.h"
#include "WindowElements.h"

UFOPhysicsComponent::UFOPhysicsComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements,
                                            GameEntityFactory* gameEntityFactory)
:   gameEntityFactory(gameEntityFactory),
    render(NULL),
    velocity(0,300),
    velocityPerSecond(500),
    shooting(true)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    render = gameEntity->getRenderComponent();
}

UFOPhysicsComponent::~UFOPhysicsComponent()
{
}

void UFOPhysicsComponent::update()
{
	float timeSinceLastFrame = timeBasedMovementTimer.getTimeOnTimer() / 1000.f;
    //x = x + speedPerSeconds*secondsSinceLastFrame
    //gameEntity->xPos += (xVel * timeSinceLastFrame);
    //gameEntity->position += velocity*timeSinceLastFrame;

    Vector2D playerPosition = gameEntityFactory->getPlayerPosition();
    if (playerPosition.x < gameEntity->position.x)
    {
        velocity.x = -150;
        velocity.y = sqrt(300*300 - 150*150);
    }
    else if (playerPosition.x > gameEntity->position.x)
    {
        velocity.x = 150;
        velocity.y = sqrt(300*300 - 150*150);
    }
    else
    {
        velocity.x = 0;
        velocity.y = 300;
    }

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
    }
    timeBasedMovementTimer.stop();
    timeBasedMovementTimer.start();

}

void UFOPhysicsComponent::pauseTimers()
{
    //timeBasedMovementTimer.pause();
    //projectileCapTimer.pause();
}

void UFOPhysicsComponent::resumeTimers()
{
    //timeBasedMovementTimer.resume();
    //projectileCapTimer.resume();
}

void UFOPhysicsComponent::onHit()
{
    if (!decrementHealth(1))
    {
        onDestroy();
    }
}

void UFOPhysicsComponent::onDestroy()
{
    //gameEntityFactory->createExplosion(gameEntity);
    SpawnData data;
    data.type = "explosion";
    data.x = gameEntity->position.x;
    data.y = gameEntity->position.y;
    data.width = render->getRenderRect().w;
    data.height = render->getRenderRect().h;
    gameEntityFactory->createEntity(data);
    gameEntity->remove = true;
    notify(gameEntity, ENEMY_DESTROYED);
}

MovementPattern* UFOPhysicsComponent::getMovementPattern()
{
    return &movement;
}

