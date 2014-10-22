/*******************************************************************//*
 * Implementation of the CollisionManager class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-18
 * @modified    2014-10-21
 *********************************************************************/
#include "CollisionManager.h"

#include <algorithm>
#include "CollisionBody.h"
#include "CollisionComponent.h"
#include "GameEntity.h"
#include "RenderComponent.h"
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

void CollisionManager::deleteCollisionObject(GameEntity* gameEntity, int flag)
{
    if (ENTITY_FRIENDLY & flag)
    {
        friendlyArray.erase(std::find(friendlyArray.begin(), friendlyArray.end(), gameEntity));
    }
    else if (ENTITY_NEUTRAL & flag)
    {
        neutralArray.erase(std::find(neutralArray.begin(), neutralArray.end(), gameEntity));
    }
    else if (ENTITY_ENEMY & flag)
    {
        enemyArray.erase(std::find(enemyArray.begin(), enemyArray.end(), gameEntity));
    }
}

bool CollisionManager::checkCollision(GameEntity* gameEntity, int flags)
{
    //CollisionBody* body = gameEntity->getCollisionComponent()->body;
    //int bodyType = body->getType();

    ///hard busted logic...
    if (ENTITY_FRIENDLY & flags)
    {
        if (checkCollisionAgainstFriendly(gameEntity)) { return true; };
    }
    if (ENTITY_NEUTRAL & flags)
    {
        if (checkCollisionAgainstNeutral(gameEntity)) { return true; };
    }
    if (ENTITY_ENEMY & flags)
    {
        if (checkCollisionAgainstEnemy(gameEntity)) { return true; };
    }

    return false;
}

bool CollisionManager::checkCollisionAgainstFriendly(GameEntity* gameEntity)
{
    for (std::vector<GameEntity*>::iterator it=friendlyArray.begin(); it!=friendlyArray.end(); it++)
    {
        if (checkCollisionBoundingRect(gameEntity, *it))
        {
            gameEntity->onDestroy();
            gameEntity->remove = true;
            (*it)->onDestroy();
            (*it)->remove = true;
            //it = friendlyArray.erase(it);
            return true;
            //std::vector<Vector2D> checkSource = gameEntity->getCollisionComponent()->body->getPoints();
            //std::vector<Vector2D> checkDest = friendlyArray[i]->getCollisionComponent()->body->getPoints();
        }
    }
    return false;
}

bool CollisionManager::checkCollisionAgainstNeutral(GameEntity* gameEntity)
{
    for (std::vector<GameEntity*>::iterator it=neutralArray.begin(); it!=neutralArray.end(); it++)
    {
        if (checkCollisionBoundingRect(gameEntity, *it))
        {
            gameEntity->onDestroy();
            gameEntity->remove = true;
            (*it)->onDestroy();
            (*it)->remove = true;
            //it = neutralArray.erase(it);
            return true;
            //std::vector<Vector2D> checkSource = gameEntity->getCollisionComponent()->body->getPoints();
            //std::vector<Vector2D> checkDest = neutralArray[i]->getCollisionComponent()->body->getPoints();
        }
    }
    return false;
}

bool CollisionManager::checkCollisionAgainstEnemy(GameEntity* gameEntity)
{
    for (std::vector<GameEntity*>::iterator it=enemyArray.begin(); it!=enemyArray.end(); it++)
    {
        if (checkCollisionBoundingRect(gameEntity, *it))
        {
            gameEntity->onDestroy();
            gameEntity->remove = true;
            (*it)->onDestroy();
            (*it)->remove = true;
            //it = enemyArray.erase(it);
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
    //SDL_Rect sourceRect = checkSource->getCollisionComponent()->body->boundingRect;
    //SDL_Rect destRect = checkDest->getCollisionComponent()->body->boundingRect;
    SDL_Rect sourceRect = checkSource->getRenderComponent()->renderRect;
    SDL_Rect destRect = checkDest->getRenderComponent()->renderRect;
    bool xAxisOverlap = ((sourceRect.x + sourceRect.w) > (destRect.x)) &&
                        ((destRect.x + destRect.w) > (sourceRect.x));
    //printf();
    if (!xAxisOverlap) { return false; }
    bool yAxisOverlap = ((sourceRect.y + sourceRect.h) > (destRect.y)) &&
                        ((destRect.y + destRect.h) > (sourceRect.y));
    if (!yAxisOverlap) { return false; }
    return true;
}
