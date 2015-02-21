/*******************************************************************//*
 * Implementation of the PlayerInstructionsInputComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-01
 * @modified    2015-02-21
 *********************************************************************/
#include "PlayerInstructionsInputComponent.h"

#include "GameEntity.h"
#include "PlayerInstructionsPhysicsComponent.h"
#include "Vector2D.h"
#include "WindowElements.h"

PlayerInstructionsInputComponent::PlayerInstructionsInputComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements)
:   physics(NULL)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    physics = dynamic_cast<PlayerInstructionsPhysicsComponent*>(gameEntity->getPhysicsComponent());
    keyStates = SDL_GetKeyboardState(0);
}

PlayerInstructionsInputComponent::~PlayerInstructionsInputComponent()
{

}

void PlayerInstructionsInputComponent::update(SDL_Event* event)
{
    physics->shooting = false;
    physics->velocity.set(0, 0);

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

        if (keyStates[SDL_SCANCODE_DOWN] == 1 || keyStates[SDL_SCANCODE_S] == 1)
        {
            physics->velocity.y = physics->velocityPerSecond;
        }

        if (keyStates[SDL_SCANCODE_UP] == 1 || keyStates[SDL_SCANCODE_W] == 1)
        {
            physics->velocity.y = -physics->velocityPerSecond;
        }

        if (keyStates[SDL_SCANCODE_RIGHT] == 1 || keyStates[SDL_SCANCODE_D] == 1)
        {
            physics->velocity.x = physics->velocityPerSecond;
        }

        if (keyStates[SDL_SCANCODE_LEFT] == 1 || keyStates[SDL_SCANCODE_A] == 1)
        {
            physics->velocity.x = -physics->velocityPerSecond;
        }
    }
}


