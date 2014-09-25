/*******************************************************************//*
 * Implementation of the PlayerProjectilePhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-08
 * @modified    2014-09-25
 *********************************************************************/
#include "PlayerProjectilePhysicsComponent.h"

#include "GameEntity.h"
#include "RenderComponent.h"
#include "WindowElements.h"

PlayerProjectilePhysicsComponent::PlayerProjectilePhysicsComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements)
:   render(NULL), velocity(0, -1500), velocityPerSecond(1500)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    render = gameEntity->getRenderComponent();
}

PlayerProjectilePhysicsComponent::~PlayerProjectilePhysicsComponent()
{

}

void PlayerProjectilePhysicsComponent::update()
{
	float timeSinceLastFrame = timeBasedMovementTimer.getTimeOnTimer() / 1000.f;

    //y = y + speedPerSeconds*secondsSinceLastFrame
    gameEntity->position += velocity*timeSinceLastFrame;
    if (gameEntity->position.y + render->renderRect.h/2 < 0)
    {
        gameEntity->remove = true;
    }
    timeBasedMovementTimer.stop();
    timeBasedMovementTimer.start();
}

void PlayerProjectilePhysicsComponent::pauseTimers()
{
    timeBasedMovementTimer.pause();
}

void PlayerProjectilePhysicsComponent::resumeTimers()
{
    timeBasedMovementTimer.resume();
}

