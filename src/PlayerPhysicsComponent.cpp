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
#include "PlayerRenderComponent.h"
#include "WindowElements.h"

PlayerPhysicsComponent::PlayerPhysicsComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements)
:   gameEntity(gameEntity), windowElements(windowElements), render(NULL),
    xVel(0), yVel(0), velocityPerSecond(500)
{
    render = dynamic_cast<PlayerRenderComponent*>(gameEntity->getRenderComponent());
}

PlayerPhysicsComponent::~PlayerPhysicsComponent()
{

}

void PlayerPhysicsComponent::update()
{
	float timeSinceLastFrame = timeBasedMovementTimer.getTimeOnTimer() / 1000.f;
    //x = x + speedPerSeconds*secondsSinceLastFrame
    gameEntity->xPos += (xVel * timeSinceLastFrame);
    if (gameEntity->xPos > windowElements->WINDOW_WIDTH)
    {
        gameEntity->xPos = windowElements->WINDOW_WIDTH;
    }
    else if (gameEntity->xPos < 0)
    {
        gameEntity->xPos = 0;
    }

    //y = y + speedPerSeconds*secondsSinceLastFrame
    gameEntity->yPos += (yVel * timeSinceLastFrame);
    if (gameEntity->yPos > windowElements->WINDOW_HEIGHT - render->spriteHeight/2)
    {
        gameEntity->yPos = windowElements->WINDOW_HEIGHT - render->spriteHeight/2;
    }
    else if (gameEntity->yPos < 0 + render->spriteHeight/2)
    {
        gameEntity->yPos = 0 + render->spriteHeight/2;
    }
    timeBasedMovementTimer.stop();
    timeBasedMovementTimer.start();
}


