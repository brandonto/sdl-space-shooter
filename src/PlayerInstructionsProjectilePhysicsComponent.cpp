/*******************************************************************//*
 * Implementation of the PlayerInstructionsProjectilePhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-01
 * @modified    2015-02-01
 *********************************************************************/
#include "PlayerInstructionsProjectilePhysicsComponent.h"

#include "GameEntity.h"
#include "RenderComponent.h"
#include "WindowElements.h"

PlayerInstructionsProjectilePhysicsComponent::PlayerInstructionsProjectilePhysicsComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements)
:   render(NULL), velocity(0, -1500), velocityPerSecond(1500)
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

PlayerInstructionsProjectilePhysicsComponent::~PlayerInstructionsProjectilePhysicsComponent()
{

}

void PlayerInstructionsProjectilePhysicsComponent::update()
{
    int collisionBuffer = 35;
	float timeSinceLastFrame = timeBasedMovementTimer.getTimeOnTimer() / 1000.f;

    //y = y + speedPerSeconds*secondsSinceLastFrame
    gameEntity->position += velocity*timeSinceLastFrame;
    if (gameEntity->position.y < yMin + collisionBuffer)
    {
        gameEntity->remove = true;
    }
    timeBasedMovementTimer.stop();
    timeBasedMovementTimer.start();
}

void PlayerInstructionsProjectilePhysicsComponent::pauseTimers()
{
    timeBasedMovementTimer.pause();
}

void PlayerInstructionsProjectilePhysicsComponent::resumeTimers()
{
    timeBasedMovementTimer.resume();
}

