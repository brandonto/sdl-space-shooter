/*******************************************************************//*
 * Implementation of the CollisionBodyRectangle class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-19
 * @modified    2014-09-20
 *********************************************************************/
#include "CollisionBodyRectangle.h"

#include "GameEntity.h"
#include "RenderComponent.h"

//NOT COMPLETE

CollisionBodyRectangle::CollisionBodyRectangle(GameEntity* gameEntity)
:   unitX(1,0), unitY(0,1), topLeftVector(0,0), topRightVector(0,0),
    bottomRightVector(0,0), bottomLeftVector(0,0)
{
    this->gameEntity = gameEntity;
    RenderComponent* render = gameEntity->getRenderComponent();
    topLeftVector.set(-render->spriteWidth/2, render->spriteHeight/2);
    topRightVector.set(render->spriteWidth/2, render->spriteHeight/2);
    bottomLeftVector.set(-render->spriteWidth/2, -render->spriteHeight/2);
    bottomRightVector.set(render->spriteWidth/2, -render->spriteHeight/2);
    //Vector2D pointsArray[4];
    //pointsArray[0] = gameEntity->position + topLeftVector;
    //pointsArray[1] = gameEntity->position + topRightVector;
    //pointsArray[2] = gameEntity->position - topLeftVector;
    //pointsArray[3] = gameEntity->position - topRightVector;
    //points(pointsArray, pointsArray + sizeof(pointsArray)/sizeof(Vector2D));
}

CollisionBodyRectangle::~CollisionBodyRectangle()
{

}

void CollisionBodyRectangle::updatePoints()
{
    //points[0] = gameEntity->position + topLeftVector;
    //points[1] = gameEntity->position + topRightVector;
    //points[2] = gameEntity->position - topLeftVector;
    //points[3] = gameEntity->position - topRightVector;
}

std::vector<Vector2D>* CollisionBodyRectangle::getPoints()
{
    return &points;
}

int CollisionBodyRectangle::getType()
{
    return typeEnum;
}

void CollisionBodyRectangle::checkCollision(GameEntity* gameEntity, int flags)
{

}
