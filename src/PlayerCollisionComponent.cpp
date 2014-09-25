/*******************************************************************//*
 * Implementation of the PlayerCollisionComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-18
 * @modified    2014-09-25
 *********************************************************************/
#include "PlayerCollisionComponent.h"

#include "CollisionBodyRectangle.h"
#include "CollisionManager.h"
#include "GameEntity.h"
#include "GameEntityManager.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "WindowElements.h"

//NOT COMPLETE

PlayerCollisionComponent::PlayerCollisionComponent(GameEntity* gameEntity,
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

PlayerCollisionComponent::~PlayerCollisionComponent()
{
    delete body;
    collisionManager->deleteCollisionObject(gameEntity, ENTITY_FRIENDLY);
}

void PlayerCollisionComponent::update()
{
    collisionManager->checkCollision(gameEntity, ENTITY_NEUTRAL | ENTITY_ENEMY);
}

