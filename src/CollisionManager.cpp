/*******************************************************************//*
 * Implementation of the CollisionManager class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-18
 * @modified    2015-02-18
 *********************************************************************/
#include "CollisionManager.h"

#include <cstdio>

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
        //printf("%s was added to friendlyArray!\n", gameEntity->getName().c_str());
        friendlyArray.push_back(gameEntity);
    }
    else if (ENTITY_NEUTRAL & flag)
    {
        //printf("%s was added to neutralArray!\n", gameEntity->getName().c_str());
        neutralArray.push_back(gameEntity);
    }
    else if (ENTITY_ENEMY & flag)
    {
        //printf("%s was added to enemyArray!\n", gameEntity->getName().c_str());
        enemyArray.push_back(gameEntity);
    }
}

void CollisionManager::deleteCollisionObject(GameEntity* gameEntity, int flag)
{
    if (ENTITY_FRIENDLY & flag)
    {
        //printf("%s was deleted from friendlyArray!\n", gameEntity->getName().c_str());
        friendlyArray.erase(std::find(friendlyArray.begin(), friendlyArray.end(), gameEntity));
    }
    else if (ENTITY_NEUTRAL & flag)
    {
        //printf("%s was deleted from neutralArray!\n", gameEntity->getName().c_str());
        neutralArray.erase(std::find(neutralArray.begin(), neutralArray.end(), gameEntity));
    }
    else if (ENTITY_ENEMY & flag)
    {
        //printf("%s was deleted from enemyArray!\n", gameEntity->getName().c_str());
        enemyArray.erase(std::find(enemyArray.begin(), enemyArray.end(), gameEntity));
    }
}

bool CollisionManager::checkCollision(GameEntity* gameEntity, int flags)
{
    if (ENTITY_FRIENDLY & flags)
    {
        //printf("%s was collision checked against friendlyArray!\n", gameEntity->getName().c_str());
        if (checkCollisionAgainstFriendly(gameEntity)) { return true; };
    }
    if (ENTITY_NEUTRAL & flags)
    {
        //printf("%s was collision checked against neutralArray!\n", gameEntity->getName().c_str());
        if (checkCollisionAgainstNeutral(gameEntity)) { return true; };
    }
    if (ENTITY_ENEMY & flags)
    {
        //printf("%s was collision checked against enemyArray!\n", gameEntity->getName().c_str());
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
            //gameEntity->onHit();
            (*it)->onHit();
            //it = friendlyArray.erase(it);
            return true;
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
            //gameEntity->onHit();
            (*it)->onHit();
            //it = neutralArray.erase(it);
            return true;
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
            //gameEntity->onHit();
            (*it)->onHit();
            //it = enemyArray.erase(it);
            return true;
        }
    }
    return false;
}

bool CollisionManager::checkCollisionBoundingRect(GameEntity* checkSource,
                                                  GameEntity* checkDest)
{
    SDL_Rect sourceRect = checkSource->getRenderComponent()->getRenderRect();
    //printf("sourcename = %s, x = %d\n", checkSource->getName().c_str(), sourceRect.x);
    //printf("sourcename = %s, y = %d\n", checkSource->getName().c_str(), sourceRect.y);
    //printf("sourcename = %s, w = %d\n", checkSource->getName().c_str(), sourceRect.w);
    //printf("sourcename = %s, h = %d\n", checkSource->getName().c_str(), sourceRect.h);
    SDL_Rect destRect = checkDest->getRenderComponent()->getRenderRect();
    //printf("destname = %s, x = %d\n", checkDest->getName().c_str(), destRect.x);
    //printf("destname = %s, y = %d\n", checkDest->getName().c_str(), destRect.y);
    //printf("destname = %s, w = %d\n", checkDest->getName().c_str(), destRect.w);
    //printf("destname = %s, h = %d\n", checkDest->getName().c_str(), destRect.h);
    bool xAxisOverlap = ((sourceRect.x + sourceRect.w) > (destRect.x)) &&
                        ((destRect.x + destRect.w) > (sourceRect.x));
    //printf();
    if (!xAxisOverlap) { return false; }
    bool yAxisOverlap = ((sourceRect.y + sourceRect.h) > (destRect.y)) &&
                        ((destRect.y + destRect.h) > (sourceRect.y));
    if (!yAxisOverlap) { return false; }
    return true;
}
