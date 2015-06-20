/*******************************************************************//*
 * Implementation of the BackgroundPhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-13
 * @modified    2015-02-19
 *********************************************************************/
#include "BackgroundPhysicsComponent.h"

#include <cstddef>

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
	#include <SDL2/SDL.h>
#endif

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
	if (gameEntity->position.y > render->getRenderRect().h)
	{
		gameEntity->position.y = 0;
	}
}

BackgroundPhysicsComponent::~BackgroundPhysicsComponent()
{
}
