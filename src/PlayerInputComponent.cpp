/*******************************************************************//*
 * Implementation of the PlayerInputComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2014-09-06
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
}

PlayerInputComponent::~PlayerInputComponent()
{

}

void PlayerInputComponent::update(SDL_Event* event)
{
    if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
    {
        switch(event->key.keysym.scancode)
        {
            case SDL_SCANCODE_UP:
                physics->yVel -= physics->velocity;
                break;

            case SDL_SCANCODE_DOWN:
                physics->yVel += physics->velocity;
                break;

            case SDL_SCANCODE_LEFT:
                physics->xVel -= physics->velocity;
                break;

            case SDL_SCANCODE_RIGHT:
                physics->xVel += physics->velocity;
                break;
        }
    }
    else if (event->type == SDL_KEYUP && event->key.repeat == 0)
    {
        switch(event->key.keysym.scancode)
        {
            case SDL_SCANCODE_UP:
                physics->yVel += physics->velocity;
                break;

            case SDL_SCANCODE_DOWN:
                physics->yVel -= physics->velocity;
                break;

            case SDL_SCANCODE_LEFT:
                physics->xVel += physics->velocity;
                break;

            case SDL_SCANCODE_RIGHT:
                physics->xVel -= physics->velocity;
                break;
        }
    }
}


