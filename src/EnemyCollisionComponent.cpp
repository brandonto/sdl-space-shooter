/*******************************************************************//*
 * Implementation of the EnemyCollisionComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-22
 * @modified    2015-02-15
 *********************************************************************/
#include "EnemyCollisionComponent.h"

#include "CollisionBodyRectangle.h"
#include "CollisionManager.h"
#include "GameEntity.h"
#include "GameEntityManager.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "WindowElements.h"

//NOT COMPLETE

EnemyCollisionComponent::EnemyCollisionComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements,
                                            CollisionManager* collisionManager)
:   collisionManager(collisionManager), physics(NULL), render(NULL)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    physics = gameEntity->getPhysicsComponent();
    render = gameEntity->getRenderComponent();
    collisionManager->addCollisionObject(gameEntity, ENTITY_ENEMY);
    this->body = new CollisionBodyRectangle(gameEntity);
}

EnemyCollisionComponent::~EnemyCollisionComponent()
{
    delete body;
    collisionManager->deleteCollisionObject(gameEntity, ENTITY_ENEMY);
}

void EnemyCollisionComponent::update()
{
    collisionManager->checkCollision(gameEntity, ENTITY_NEUTRAL | ENTITY_FRIENDLY);
}

