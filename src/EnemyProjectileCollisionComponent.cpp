/*******************************************************************//*
 * Implementation of the EnemyProjectileCollisionComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-22
 * @modified    2014-09-22
 *********************************************************************/
#include "EnemyProjectileCollisionComponent.h"

#include "CollisionBodyRectangle.h"
#include "CollisionManager.h"
#include "GameEntity.h"
#include "GameEntityManager.h"
#include "EnemyProjectileRenderComponent.h"
#include "EnemyProjectilePhysicsComponent.h"
#include "WindowElements.h"

//NOT COMPLETE

EnemyProjectileCollisionComponent::EnemyProjectileCollisionComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements,
                                            CollisionManager* collisionManager)
:   collisionManager(collisionManager), physics(NULL), render(NULL)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    physics = dynamic_cast<EnemyProjectilePhysicsComponent*>(gameEntity->getPhysicsComponent());
    render = dynamic_cast<EnemyProjectileRenderComponent*>(gameEntity->getRenderComponent());
    collisionManager->addCollisionObject(gameEntity, ENTITY_ENEMY);
    this->body = new CollisionBodyRectangle(gameEntity);
}

EnemyProjectileCollisionComponent::~EnemyProjectileCollisionComponent()
{
    delete body;
    collisionManager->deleteCollisionObject(gameEntity, ENTITY_ENEMY);
}

void EnemyProjectileCollisionComponent::update()
{
    collisionManager->checkCollision(gameEntity, ENTITY_NEUTRAL | ENTITY_FRIENDLY);
}

