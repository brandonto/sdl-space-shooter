/*******************************************************************//*
 * Implementation of the CollisionBodyRectangle class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-19
 * @modified    2014-09-19
 *********************************************************************/
#include "CollisionBodyRectangle.h"

#include "GameEntity.h"

//NOT COMPLETE

CollisionBodyRectangle::CollisionBodyRectangle(GameEntity* gameEntity)
:   unitX(1,0), unitY(0,1)
{
    this->gameEntity = gameEntity;
}

CollisionBodyRectangle::~CollisionBodyRectangle()
{

}

int CollisionBodyRectangle::getType()
{
    return typeEnum;
}

void CollisionBodyRectangle::checkCollision(GameEntity* gameEntity, int flags)
{
}
