/*******************************************************************//*
 * Implementation of the GameEntityCollection class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2015-02-21
 *********************************************************************/
#include "GameEntityCollection.h"

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
	#include <SDL2/SDL.h>
#endif

#include "GameEntity.h"
#include "PhysicsComponent.h"
#include <algorithm>

GameEntityCollection::GameEntityCollection()
{
    //Nothing
}

GameEntityCollection::~GameEntityCollection()
{
    
}

void GameEntityCollection::add(GameEntity* gameEntity)
{
    collection.push_front(std::shared_ptr<GameEntity>(gameEntity));
}

void GameEntityCollection::remove(GameEntity* gameEntity)
{
    //collection
}

void GameEntityCollection::onEvent(SDL_Event* event)
{
    for (auto collectionIterator=collection.begin();
            collectionIterator!=collection.end();
            collectionIterator++)
    {
        (*collectionIterator)->onEvent(event);
    }
}

void GameEntityCollection::onUpdate()
{
    
    for (auto collectionIterator=collection.begin();
            collectionIterator!=collection.end();
            collectionIterator++)
    {
        (*collectionIterator)->onUpdate();
    }

    auto it_new_end = std::remove_if(collection.begin(), collection.end(), 
        [](std::shared_ptr<GameEntity> pEntity){return pEntity->remove; });

    collection.erase(it_new_end, collection.end());
}

void GameEntityCollection::onRender()
{
    for (auto collectionIterator=collection.begin();
            collectionIterator!=collection.end();
            collectionIterator++)
    {
        (*collectionIterator)->onRender();
    }
}

void GameEntityCollection::onPauseTimers()
{
    for (auto collectionIterator=collection.begin();
            collectionIterator!=collection.end();
            collectionIterator++)
    {
        PhysicsComponent* physics = (*collectionIterator)->getPhysicsComponent();
        if (physics != NULL)
        {
            physics->pauseTimers();
        }
    }
}

void GameEntityCollection::onResumeTimers()
{
    for (auto collectionIterator=collection.begin();
            collectionIterator!=collection.end();
            collectionIterator++)
    {
        PhysicsComponent* physics = (*collectionIterator)->getPhysicsComponent();
        if (physics != NULL)
        {
            physics->resumeTimers();
        }
    }
}
