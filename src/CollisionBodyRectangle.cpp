/*******************************************************************//*
 * Implementation of the CollisionBodyRectangle class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-19
 * @modified    2015-02-06
 *********************************************************************/
#include "CollisionBodyRectangle.h"

#include "GameEntity.h"
#include "RenderComponent.h"

//NOT COMPLETE

CollisionBodyRectangle::CollisionBodyRectangle(GameEntity* gameEntity)
:   unitX(1,0),
    unitY(0,1),
    topLeftVector(0,0),
    topRightVector(0,0),
    bottomRightVector(0,0),
    bottomLeftVector(0,0)
{
    this->gameEntity = gameEntity;

    int width = gameEntity->getRenderComponent()->getTexture()->getSpriteWidth();
    int height = gameEntity->getRenderComponent()->getTexture()->getSpriteHeight();

    topLeftVector.set(-width/2, height/2);
    topRightVector.set(width/2, height/2);
    bottomLeftVector.set(-width/2, -height/2);
    bottomRightVector.set(width/2, -height/2);
    points.push_back(gameEntity->position + topLeftVector);
    points.push_back(gameEntity->position + topRightVector);
    points.push_back(gameEntity->position - topLeftVector);
    points.push_back(gameEntity->position - topRightVector);

    //boundingRect.x = points[0].x;
    //boundingRect.y = points[0].y;
    boundingRect.x = gameEntity->getRenderComponent()->getRenderRect().x;
    boundingRect.y = gameEntity->getRenderComponent()->getRenderRect().y;
    boundingRect.w = width;
    boundingRect.h = height;
}

CollisionBodyRectangle::~CollisionBodyRectangle()
{

}

void CollisionBodyRectangle::update()
{
    //points[0] = gameEntity->position + topLeftVector;
    //points[1] = gameEntity->position + topRightVector;
    //points[2] = gameEntity->position - topLeftVector;
    //points[3] = gameEntity->position - topRightVector;

    //boundingRect.x  = points[0].x;
    //boundingRect.y  = points[0].y;
    boundingRect.x = gameEntity->getRenderComponent()->getRenderRect().x;
    boundingRect.y = gameEntity->getRenderComponent()->getRenderRect().y;
}

std::vector<Vector2D>* CollisionBodyRectangle::getPoints()
{
    return &points;
}

int CollisionBodyRectangle::getType()
{
    return typeEnum;
}

