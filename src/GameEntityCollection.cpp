/*******************************************************************//*
 * Implementation of the GameEntityCollection class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2015-02-16
 *********************************************************************/
#include "GameEntityCollection.h"

#ifdef _WIN32
	#include <SDL.h>
#endif
#ifdef linux
	#include <SDL2/SDL.h>
#endif

#include <GameEntity.h>
#include <PhysicsComponent.h>

GameEntityCollection::GameEntityCollection()
{
    //Nothing
}

GameEntityCollection::~GameEntityCollection()
{
    std::list<GameEntity*>::iterator collectionIterator;
    for (   collectionIterator=collection.begin();
            collectionIterator!=collection.end();
            collectionIterator++)
    {
        delete (*collectionIterator);
    }
}

void GameEntityCollection::add(GameEntity* gameEntity)
{
    collection.push_front(gameEntity);
}

void GameEntityCollection::remove(GameEntity* gameEntity)
{
    //collection
}

void GameEntityCollection::onEvent(SDL_Event* event)
{
    std::list<GameEntity*>::iterator collectionIterator;
    for (   collectionIterator=collection.begin();
            collectionIterator!=collection.end();
            collectionIterator++)
    {
        (*collectionIterator)->onEvent(event);
    }
}

void GameEntityCollection::onUpdate()
{
    std::list<GameEntity*>::iterator collectionIterator;
    for (   collectionIterator=collection.begin();
            collectionIterator!=collection.end();
            collectionIterator++)
    {
        (*collectionIterator)->onUpdate();
    }

    for (   collectionIterator=collection.begin();
            collectionIterator!=collection.end();
            collectionIterator++)
    {
        if ((*collectionIterator)->remove)
        {
            delete *collectionIterator;
            collectionIterator = collection.erase(collectionIterator);
            collectionIterator--;
        }
    }
}

void GameEntityCollection::onRender()
{
    std::list<GameEntity*>::iterator collectionIterator;
    for (   collectionIterator=collection.begin();
            collectionIterator!=collection.end();
            collectionIterator++)
    {
        (*collectionIterator)->onRender();
    }
}

void GameEntityCollection::onPauseTimers()
{
    std::list<GameEntity*>::iterator collectionIterator;
    for (   collectionIterator=collection.begin();
            collectionIterator!=collection.end();
            collectionIterator++)
    {
        (*collectionIterator)->getPhysicsComponent()->pauseTimers();
    }
}

void GameEntityCollection::onResumeTimers()
{
    std::list<GameEntity*>::iterator collectionIterator;
    for (   collectionIterator=collection.begin();
            collectionIterator!=collection.end();
            collectionIterator++)
    {
        (*collectionIterator)->getPhysicsComponent()->resumeTimers();
    }
}
