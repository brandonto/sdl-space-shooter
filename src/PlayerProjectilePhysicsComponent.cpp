/*******************************************************************//*
 * Implementation of the PlayerProjectilePhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-08
 * @modified    2015-02-06
 *********************************************************************/
#include "PlayerProjectilePhysicsComponent.h"

#include "GameEntity.h"
#include "RenderComponent.h"
#include "WindowElements.h"

PlayerProjectilePhysicsComponent::PlayerProjectilePhysicsComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements)
:   render(NULL),
    velocity(0,-1500),
    velocityPerSecond(1500)
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

    gameEntity->position += velocity*timeSinceLastFrame;
    if (gameEntity->position.y + render->getRenderRect().h/2 < 0)
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

