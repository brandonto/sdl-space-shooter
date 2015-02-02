/*******************************************************************//*
 * Implementation of the PlayerInstructionsPhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-01
 * @modified    2015-02-01
 *********************************************************************/
#include "PlayerInstructionsPhysicsComponent.h"

#include "GameEntity.h"
#include "GameEntityManager.h"
#include "RenderComponent.h"
#include "WindowElements.h"

PlayerInstructionsPhysicsComponent::PlayerInstructionsPhysicsComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements,
                                            GameEntityManager* gameEntityManager)
:   gameEntityManager(gameEntityManager), render(NULL),
    velocity(0, 0), velocityPerSecond(500), shooting(false)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    render = gameEntity->getRenderComponent();

    xGrid = windowElements->WINDOW_WIDTH/60;
    yGrid = windowElements->WINDOW_HEIGHT/48;

    // These are the magic numbers for the mini screen
    SDL_Rect temp;
    temp.x = 23*xGrid;
    temp.y = 12*yGrid;
    temp.w = 34*xGrid;
    temp.h = 34*yGrid;

    xMin = temp.x;
    yMin = temp.y;
    xMax = temp.x + temp.w;
    yMax = temp.y + temp.h;
}

PlayerInstructionsPhysicsComponent::~PlayerInstructionsPhysicsComponent()
{
}

void PlayerInstructionsPhysicsComponent::update()
{
    int collisionBuffer = 20;
	float timeSinceLastFrame = timeBasedMovementTimer.getTimeOnTimer() / 1000.f;
    //x = x + speedPerSeconds*secondsSinceLastFrame
    //gameEntity->xPos += (xVel * timeSinceLastFrame);
    gameEntity->position += velocity*timeSinceLastFrame;

    if (gameEntity->position.x > xMax - render->spriteHeight/2 - collisionBuffer)
    {
        gameEntity->position.x = xMax - render->spriteHeight/2 - collisionBuffer;
    }
    else if (gameEntity->position.x < xMin + render->spriteHeight/2 + collisionBuffer)
    {
        gameEntity->position.x = xMin + render->spriteHeight/2 + collisionBuffer;
    }

    //y = y + speedPerSeconds*secondsSinceLastFrame
    //gameEntity->yPos += (yVel * timeSinceLastFrame);
    if (gameEntity->position.y > yMax - render->spriteHeight/2 - collisionBuffer)
    {
        gameEntity->position.y = yMax - render->spriteHeight/2 - collisionBuffer;
    }
    else if (gameEntity->position.y < yMin + render->spriteHeight/2 + collisionBuffer)
    {
        gameEntity->position.y = yMin + render->spriteHeight/2 + collisionBuffer;
    }
    timeBasedMovementTimer.stop();
    timeBasedMovementTimer.start();

    if (shooting)
    {
        if (projectileCapTimer.isStarted())
        {
            if (projectileCapTimer.getTimeOnTimer()>150)
            {
                gameEntityManager->createPlayerInstructionsProjectile(gameEntity);
                projectileCapTimer.stop();
            }
        }
        else
        {
            gameEntityManager->createPlayerInstructionsProjectile(gameEntity);
        }
        projectileCapTimer.start();
    }
}

void PlayerInstructionsPhysicsComponent::pauseTimers()
{
    timeBasedMovementTimer.pause();
    projectileCapTimer.pause();
}

void PlayerInstructionsPhysicsComponent::resumeTimers()
{
    timeBasedMovementTimer.resume();
    projectileCapTimer.resume();
}

void PlayerInstructionsPhysicsComponent::onDestroy()
{
    gameEntityManager->createExplosion(gameEntity);
}
