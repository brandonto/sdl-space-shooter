/*******************************************************************//*
 * Implementation of the PlayerInputComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2014-09-19
 *********************************************************************/
#include "PlayerInputComponent.h"

#include "GameEntity.h"
#include "PlayerPhysicsComponent.h"
#include "Vector2D.h"
#include "WindowElements.h"

PlayerInputComponent::PlayerInputComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements)
:   physics(NULL)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    physics = dynamic_cast<PlayerPhysicsComponent*>(gameEntity->getPhysicsComponent());
    keyStates = SDL_GetKeyboardState(0);
}

PlayerInputComponent::~PlayerInputComponent()
{

}

void PlayerInputComponent::update(SDL_Event* event)
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

