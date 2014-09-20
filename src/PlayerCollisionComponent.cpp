/*******************************************************************//*
 * Implementation of the PlayerCollisionComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-18
 * @modified    2014-09-19
 *********************************************************************/
#include "PlayerCollisionComponent.h"

#include "CollisionManager.h"
#include "GameEntity.h"
#include "GameEntityManager.h"
#include "PlayerRenderComponent.h"
#include "PlayerPhysicsComponent.h"
#include "WindowElements.h"

//NOT COMPLETE

PlayerCollisionComponent::PlayerCollisionComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements,
                                            CollisionManager* collisionManager)
:   gameEntity(gameEntity), windowElements(windowElements),
    collisionManager(collisionManager), physics(NULL), render(NULL)
{
    physics = dynamic_cast<PlayerPhysicsComponent*>(gameEntity->getPhysicsComponent());
    render = dynamic_cast<PlayerRenderComponent*>(gameEntity->getRenderComponent());
    collisionManager->addCollisionObject(gameEntity, ENTITY_FRIENDLY);
}

PlayerCollisionComponent::~PlayerCollisionComponent()
{

}

void PlayerCollisionComponent::update()
{
    collisionManager->checkCollision(gameEntity, ENTITY_NEUTRAL | ENTITY_ENEMY);
}

