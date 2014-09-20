/*******************************************************************//*
 * Implementation of the MeteorPhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-14
 * @modified    2014-09-19
 *********************************************************************/
#include "MeteorPhysicsComponent.h"

#include "GameEntity.h"
#include "GameEntityManager.h"
#include "MeteorRenderComponent.h"
#include "WindowElements.h"

MeteorPhysicsComponent::MeteorPhysicsComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements)
:   gameEntityManager(gameEntityManager), render(NULL),
    velocity(-15, 5), velocityPerSecond(0),
    angleIncrementCounter(0), angleIncrementModulus(1)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    render = dynamic_cast<MeteorRenderComponent*>(gameEntity->getRenderComponent());
}

MeteorPhysicsComponent::~MeteorPhysicsComponent()
{

}

void MeteorPhysicsComponent::update()
{
    angleIncrementCounter++;
    if (angleIncrementCounter % angleIncrementModulus == 0)
    {
        render->angle+=0.10;
    }
    if (render->angle >= 360)
    {
        render->angle = 0;
    }

	float timeSinceLastFrame = timeBasedMovementTimer.getTimeOnTimer() / 1000.f;
    //position = position + speedPerSecond*secondsSinceLastFrame
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
    }

    timeBasedMovementTimer.stop();
    timeBasedMovementTimer.start();

}

void MeteorPhysicsComponent::pauseTimers()
{
    timeBasedMovementTimer.pause();
}

void MeteorPhysicsComponent::resumeTimers()
{
    timeBasedMovementTimer.resume();
}

