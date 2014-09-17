/*******************************************************************//*
 * Implementation of the EnemyProjectilePhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-17
 * @modified    2014-09-17
 *********************************************************************/
#include "EnemyProjectilePhysicsComponent.h"

#include "GameEntity.h"
#include "EnemyProjectileRenderComponent.h"
#include "WindowElements.h"

EnemyProjectilePhysicsComponent::EnemyProjectilePhysicsComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements)
:   gameEntity(gameEntity), windowElements(windowElements), render(NULL),
    velocity(0, 400), velocityPerSecond(1500)
{
    render = dynamic_cast<EnemyProjectileRenderComponent*>(gameEntity->getRenderComponent());
}

EnemyProjectilePhysicsComponent::~EnemyProjectilePhysicsComponent()
{

}

void EnemyProjectilePhysicsComponent::update()
{
	float timeSinceLastFrame = timeBasedMovementTimer.getTimeOnTimer() / 1000.f;

    //y = y + speedPerSeconds*secondsSinceLastFrame
    gameEntity->position += velocity*timeSinceLastFrame;
    if (gameEntity->position.y - render->renderRect.h/2 > windowElements->WINDOW_HEIGHT)
    {
        gameEntity->remove = true;
    }
    timeBasedMovementTimer.stop();
    timeBasedMovementTimer.start();
}

void EnemyProjectilePhysicsComponent::pauseTimers()
{
    timeBasedMovementTimer.pause();
}

void EnemyProjectilePhysicsComponent::resumeTimers()
{
    timeBasedMovementTimer.resume();
}

