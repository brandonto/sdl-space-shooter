/*******************************************************************//*
 * Implementation of the PlayerProjectilePhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-08
 * @modified    2015-02-17
 *********************************************************************/
#include "PlayerProjectilePhysicsComponent.h"

#include "AudioSystem.h"
#include "GameEntity.h"
#include "GameEntityFactory.h"
#include "RenderComponent.h"
#include "WindowElements.h"

PlayerProjectilePhysicsComponent::PlayerProjectilePhysicsComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements,
                                            GameEntityFactory* factory)
:   render(NULL),
    velocity(0,-1500),
    velocityPerSecond(1500)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    this->factory = factory;
    render = gameEntity->getRenderComponent();
    AudioSystem::getInstance()->playSound("laser");
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

void PlayerProjectilePhysicsComponent::onHit()
{
    AudioSystem::getInstance()->playSound("laserHit");
    onDestroy();
}

void PlayerProjectilePhysicsComponent::onDestroy()
{
    SpawnData data;
    data.type = "playerProjectileHit";
    data.x = gameEntity->position.x;
    data.y = gameEntity->position.y;
    factory->createEntity(data);
    gameEntity->remove = true;
}

