/*******************************************************************//*
 * Implementation of the CollisionManager class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-18
 * @modified    2014-09-22
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
    CollisionBody* body = gameEntity->getCollisionComponent()->body;
    int bodyType = body->getType();

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
    for (int i=0; i<friendlyArray.size(); i++)
    {
        if (checkCollisionBoundingRect(gameEntity, friendlyArray[i]))
        {
            gameEntity->remove = true;
            return true;
            //std::vector<Vector2D> checkSource = gameEntity->getCollisionComponent()->body->getPoints();
            //std::vector<Vector2D> checkDest = friendlyArray[i]->getCollisionComponent()->body->getPoints();
        }
    }
    return false;
}

bool CollisionManager::checkCollisionAgainstNeutral(GameEntity* gameEntity)
{
    for (int i=0; i<neutralArray.size(); i++)
    {
        if (checkCollisionBoundingRect(gameEntity, neutralArray[i]))
        {
            gameEntity->remove = true;
            return true;
            //std::vector<Vector2D> checkSource = gameEntity->getCollisionComponent()->body->getPoints();
            //std::vector<Vector2D> checkDest = neutralArray[i]->getCollisionComponent()->body->getPoints();
        }
    }
    return false;
}

bool CollisionManager::checkCollisionAgainstEnemy(GameEntity* gameEntity)
{
    for (int i=0; i<enemyArray.size(); i++)
    {
        if (checkCollisionBoundingRect(gameEntity, enemyArray[i]))
        {
            gameEntity->remove = true;
            return true;
            //std::vector<Vector2D> checkSource = gameEntity->getCollisionComponent()->body->getPoints();
            //std::vector<Vector2D> checkDest = enemyArray[i]->getCollisionComponent()->body->getPoints();
        }
    }
    return false;
}

bool CollisionManager::checkCollisionBoundingRect(GameEntity* checkSource,
                                                  GameEntity* checkDest)
{
    SDL_Rect sourceRect = checkSource->getCollisionComponent()->body->boundingRect;
    SDL_Rect destRect = checkDest->getCollisionComponent()->body->boundingRect;
    //return ( (  sourceRect.x - destRect.x 

}
