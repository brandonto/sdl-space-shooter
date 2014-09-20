/*******************************************************************//*
 * Implementation of the CollisionManager class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-18
 * @modified    2014-09-19
 *********************************************************************/
#include "CollisionManager.h"

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
    if (ENTITY_FRIENDLY & flags)
    {
        gameEntity->getCollisionComponent();
    }
    return collision;
}
