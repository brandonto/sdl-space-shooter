/*******************************************************************//*
 * Implementation of the GameEntityCollection class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-08-10
 *********************************************************************/
#include "GameEntityCollection.h"

void GameEntityCollection::add(GameEntity* gameEntity)
{
    collection.push_front(gameEntity);
}

void GameEntityCollection::remove(GameEntity* gameEntity)
{
    //TBD
}
