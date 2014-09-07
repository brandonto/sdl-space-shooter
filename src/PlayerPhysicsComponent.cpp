/*******************************************************************//*
 * Implementation of the PlayerPhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2014-09-06
 *********************************************************************/
#include "PlayerPhysicsComponent.h"

#include "GameEntity.h"
#include "WindowElements.h"

PlayerPhysicsComponent::PlayerPhysicsComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements)
:   gameEntity(gameEntity), windowElements(windowElements),
    xVel(0), yVel(0), velocity(5)
{
}

PlayerPhysicsComponent::~PlayerPhysicsComponent()
{

}

void PlayerPhysicsComponent::update()
{
    gameEntity->xPos += xVel;
    if (gameEntity->xPos > windowElements->WINDOW_WIDTH)
    {
        gameEntity->xPos = windowElements->WINDOW_WIDTH;
    }
    else if (gameEntity->xPos < 0)
    {
        gameEntity->xPos = 0;
    }

    gameEntity->yPos += yVel;
    if (gameEntity->yPos > windowElements->WINDOW_HEIGHT)
    {
        gameEntity->yPos = windowElements->WINDOW_HEIGHT;
    }
    else if (gameEntity->yPos < 0)
    {
        gameEntity->yPos = 0;
    }
}


