/*******************************************************************//*
 * Implementation of the BackgroundPhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-13
 * @modified    2014-09-25
 *********************************************************************/
#include "BackgroundPhysicsComponent.h"

#include <cstddef>
#include <SDL2/SDL.h>
#include "RenderComponent.h"
#include "GameEntity.h"
#include "SDL_util.h"
#include "WindowElements.h"

BackgroundPhysicsComponent::BackgroundPhysicsComponent(GameEntity* gameEntity,
                                                    WindowElements* windowElements)
:   render(NULL), offsetIncrementCounter(0), offsetIncrementModulus(3)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    render = gameEntity->getRenderComponent();
}

void BackgroundPhysicsComponent::update()
{
    offsetIncrementCounter++;
    if (offsetIncrementCounter % offsetIncrementModulus == 0)
    {
        gameEntity->position.y += 1;
    }
	if (gameEntity->position.y > render->renderRect.h)
	{
		gameEntity->position.y = 0;
	}
}

BackgroundPhysicsComponent::~BackgroundPhysicsComponent()
{
}
