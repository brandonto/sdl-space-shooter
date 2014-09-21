/*******************************************************************//*
 * Implementation of the CollisionManager class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-18
 * @modified    2014-09-20
 *********************************************************************/
#include "CollisionManager.h"

#include "CollisionBody.h"
#include "CollisionComponent.h"
#include "GameEntity.h"
#include "WindowElements.h"

//NOT COMPLETE

CollisionManager::CollisionManager(WindowElements* windowElements)
:   windowElements(windowElements), friendlyArray(NULL), neutralArray(NULL), enemyArray(NULL)
{
}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::addCollisionObject(GameEntity* gameEntity, int flag)
{
    if (ENTITY_FRIENDLY & flag)
    {
        friendlyArray.push_back(gameEntity);
    }
    else if (ENTITY_NEUTRAL & flag)
    {
        neutralArray.push_back(gameEntity);
    }
    else if (ENTITY_ENEMY & flag)
    {
        enemyArray.push_back(gameEntity);
    }
}

bool CollisionManager::checkCollision(GameEntity* gameEntity, int flags)
{
    bool collision = false;
    //CollisionBody* body = gameEntity->getCollisionComponent()->body;
    //int bodyType = body->getType();

    if (ENTITY_FRIENDLY & flags)
    {
        if (!collision && checkCollisionAgainstFriendly(gameEntity)) { collision = true; };
    }
    if (ENTITY_NEUTRAL & flags)
    {
        if (!collision && checkCollisionAgainstNeutral(gameEntity)) { collision = true; };
    }
    if (ENTITY_ENEMY & flags)
    {
        if (!collision && checkCollisionAgainstEnemy(gameEntity)) { collision = true; };
    }

    return collision;
}

bool CollisionManager::checkCollisionAgainstFriendly(GameEntity* gameEntity)
{

}

bool CollisionManager::checkCollisionAgainstNeutral(GameEntity* gameEntity)
{

}

bool CollisionManager::checkCollisionAgainstEnemy(GameEntity* gameEntity)
{

}
