/*******************************************************************//*
 * Implementation of the PlayerInputComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2014-09-09
 *********************************************************************/
#include "PlayerInputComponent.h"

#include "GameEntity.h"
#include "PlayerPhysicsComponent.h"
#include "WindowElements.h"

PlayerInputComponent::PlayerInputComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements)
:   gameEntity(gameEntity), windowElements(windowElements), physics(NULL)
{
    physics = dynamic_cast<PlayerPhysicsComponent*>(gameEntity->getPhysicsComponent());
    keyStates = SDL_GetKeyboardState(0);
}

PlayerInputComponent::~PlayerInputComponent()
{

}

void PlayerInputComponent::update(SDL_Event* event)
{
    physics->shooting = false;
    physics->xVel = 0;
    physics->yVel = 0;

    if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP)
    {
        keyStates = SDL_GetKeyboardState(0);
    }

    if (keyStates != 0)
    {
        if (keyStates[SDL_SCANCODE_SPACE] == 1)
        {
            physics->shooting = true;
        }

        if (keyStates[SDL_SCANCODE_UP] == 1)
        {
            physics->yVel = -physics->velocityPerSecond;
        }

        if (keyStates[SDL_SCANCODE_DOWN] == 1)
        {
            physics->yVel = physics->velocityPerSecond;
        }

        if (keyStates[SDL_SCANCODE_LEFT] == 1)
        {
            physics->xVel = -physics->velocityPerSecond;
        }

        if (keyStates[SDL_SCANCODE_RIGHT] == 1)
        {
            physics->xVel = physics->velocityPerSecond;
        }
    }
}

