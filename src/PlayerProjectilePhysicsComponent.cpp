/*******************************************************************//*
 * Implementation of the PlayerProjectilePhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-08
 * @modified    2014-09-12
 *********************************************************************/
#include "PlayerProjectilePhysicsComponent.h"

#include "GameEntity.h"
#include "PlayerProjectileRenderComponent.h"
#include "WindowElements.h"

PlayerProjectilePhysicsComponent::PlayerProjectilePhysicsComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements)
:   gameEntity(gameEntity), windowElements(windowElements), render(NULL),
    velocity(0, 1500), velocityPerSecond(1500)
{
    render = dynamic_cast<PlayerProjectileRenderComponent*>(gameEntity->getRenderComponent());
}

PlayerProjectilePhysicsComponent::~PlayerProjectilePhysicsComponent()
{

}

void PlayerProjectilePhysicsComponent::update()
{
	float timeSinceLastFrame = timeBasedMovementTimer.getTimeOnTimer() / 1000.f;

    //y = y + speedPerSeconds*secondsSinceLastFrame
    gameEntity->position -= velocity*timeSinceLastFrame;
    timeBasedMovementTimer.stop();
    timeBasedMovementTimer.start();
}


