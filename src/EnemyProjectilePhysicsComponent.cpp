/*******************************************************************//*
 * Implementation of the EnemyProjectilePhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-17
 * @modified    2015-02-16
 *********************************************************************/
#include "EnemyProjectilePhysicsComponent.h"

#include <string>
#include "GameEntity.h"
#include "GameEntityFactory.h"
#include "RenderComponent.h"
#include "WindowElements.h"

EnemyProjectilePhysicsComponent::EnemyProjectilePhysicsComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements,
                                            GameEntityFactory* factory)
:   render(NULL),
    velocity(0,400),
    velocityPerSecond(1500)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    this->factory = factory;
    render = gameEntity->getRenderComponent();
}

EnemyProjectilePhysicsComponent::~EnemyProjectilePhysicsComponent()
{
}

void EnemyProjectilePhysicsComponent::update()
{
	float timeSinceLastFrame = timeBasedMovementTimer.getTimeOnTimer() / 1000.f;

    //y = y + speedPerSeconds*secondsSinceLastFrame
    gameEntity->position += velocity*timeSinceLastFrame;

    int height = render->getRenderRect().h;
    if (gameEntity->position.y - height/2 > windowElements->WINDOW_HEIGHT)
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

void EnemyProjectilePhysicsComponent::onDestroy()
{
    SpawnData data;
    data.type = "enemyProjectileHit";
    data.x = gameEntity->position.x;
    data.y = gameEntity->position.y;
    factory->createEntity(data);
}

