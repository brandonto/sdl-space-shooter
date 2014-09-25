/*******************************************************************//*
 * Implementation of the PlayerProjectileCollisionComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-22
 * @modified    2014-09-25
 *********************************************************************/
#include "PlayerProjectileCollisionComponent.h"

#include "CollisionBodyRectangle.h"
#include "CollisionManager.h"
#include "GameEntity.h"
#include "GameEntityManager.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "WindowElements.h"

//NOT COMPLETE

PlayerProjectileCollisionComponent::PlayerProjectileCollisionComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements,
                                            CollisionManager* collisionManager)
:   collisionManager(collisionManager), physics(NULL), render(NULL)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    physics = gameEntity->getPhysicsComponent();
    render = gameEntity->getRenderComponent();
    collisionManager->addCollisionObject(gameEntity, ENTITY_FRIENDLY);
    this->body = new CollisionBodyRectangle(gameEntity);
}

PlayerProjectileCollisionComponent::~PlayerProjectileCollisionComponent()
{
    delete body;
    collisionManager->deleteCollisionObject(gameEntity, ENTITY_FRIENDLY);
}

void PlayerProjectileCollisionComponent::update()
{
    collisionManager->checkCollision(gameEntity, ENTITY_NEUTRAL | ENTITY_ENEMY);
}

