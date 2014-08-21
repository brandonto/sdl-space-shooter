/*******************************************************************//*
 * Implementation of the GameEntityCollection class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-08-20
 *********************************************************************/
#include "GameEntityCollection.h"

#include "GameEntity.h"

void GameEntityCollection::add(GameEntity* gameEntity)
{
    collection.push_front(gameEntity);
}

void GameEntityCollection::remove(GameEntity* gameEntity)
{
    //TBD
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
