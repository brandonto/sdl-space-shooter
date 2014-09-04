/*******************************************************************//*
 * Implementation of the GameEntityCollection class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-09-03
 *********************************************************************/
#include "GameEntityCollection.h"

#include <SDL2/SDL.h>
#include <GameEntity.h>

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
    //TBD
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
