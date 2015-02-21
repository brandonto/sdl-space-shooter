/*******************************************************************//*
 * Implementation of the PlayerInstructionsPhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-01
 * @modified    2015-02-21
 *********************************************************************/
#include "PlayerInstructionsPhysicsComponent.h"

#include "GameEntity.h"
#include "GameEntityFactory.h"
#include "Level.h" // For SpawnData structure
#include "RenderComponent.h"
#include "WindowElements.h"

PlayerInstructionsPhysicsComponent::PlayerInstructionsPhysicsComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements,
                                            GameEntityFactory* gameEntityFactory)
:   gameEntityFactory(gameEntityFactory),
    render(NULL),
    velocity(0,0),
    velocityPerSecond(500),
    shooting(false)
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
	float timeSinceLastFrame = timeBasedMovementTimer.getTimeOnTimer() / 1000.f;
    //x = x + speedPerSeconds*secondsSinceLastFrame
    //gameEntity->xPos += (xVel * timeSinceLastFrame);
    gameEntity->position += velocity*timeSinceLastFrame;

    int spriteWidth = render->getTexture()->getSpriteWidth();
    int spriteHeight = render->getTexture()->getSpriteHeight();

    if (gameEntity->position.x > xMax - spriteWidth/2 - COLLISION_BUFFER)
    {
        gameEntity->position.x = xMax - spriteWidth/2 - COLLISION_BUFFER;
    }
    else if (gameEntity->position.x < xMin + spriteWidth/2 + COLLISION_BUFFER)
    {
        gameEntity->position.x = xMin + spriteWidth/2 + COLLISION_BUFFER;
    }

    //y = y + speedPerSeconds*secondsSinceLastFrame
    //gameEntity->yPos += (yVel * timeSinceLastFrame);
    if (gameEntity->position.y > yMax - spriteHeight/2 - COLLISION_BUFFER)
    {
        gameEntity->position.y = yMax - spriteHeight/2 - COLLISION_BUFFER;
    }
    else if (gameEntity->position.y < yMin + spriteHeight/2 + COLLISION_BUFFER)
    {
        gameEntity->position.y = yMin + spriteHeight/2 + COLLISION_BUFFER;
    }
    timeBasedMovementTimer.stop();
    timeBasedMovementTimer.start();

    if (shooting)
    {
        if (projectileCapTimer.isStarted())
        {
            if (projectileCapTimer.getTimeOnTimer()>150)
            {
                //gameEntityFactory->createPlayerInstructionsProjectile(gameEntity);
                SpawnData data;
                data.type = "playerInstructionsProjectile";
                data.x = gameEntity->position.x;
                data.y = gameEntity->position.y - render->getRenderRect().h/2;
                gameEntityFactory->createEntity(data);
                projectileCapTimer.stop();
            }
        }
        else
        {
            //gameEntityFactory->createPlayerInstructionsProjectile(gameEntity);
            SpawnData data;
            data.type = "playerInstructionsProjectile";
            data.x = gameEntity->position.x;
            data.y = gameEntity->position.y - render->getRenderRect().h/2;
            gameEntityFactory->createEntity(data);
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
    //gameEntityFactory->createExplosion(gameEntity);
    SpawnData data;
    data.type = "explosion";
    data.x = gameEntity->position.x;
    data.y = gameEntity->position.y;
    data.width = render->getRenderRect().w;
    data.height = render->getRenderRect().h;
    gameEntityFactory->createEntity(data);
}
