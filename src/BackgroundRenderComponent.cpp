/*******************************************************************//*
 * Implementation of the BackgroundRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-17
 * @modified    2014-09-14
 *********************************************************************/
#include "BackgroundRenderComponent.h"

#include <cstddef>
#include <SDL2/SDL.h>
#include "GameEntity.h"
#include "SDL_util.h"
#include "WindowElements.h"

BackgroundRenderComponent::BackgroundRenderComponent(GameEntity* gameEntity,
                                                    WindowElements* windowElements)
:   sprite(NULL), windowElements(windowElements), gameEntity(gameEntity)
{
    sprite=SDL_util::create_background_texture(windowElements, "bin/graphics/background/darkPurple.png");
    SDL_QueryTexture(sprite, NULL, NULL, &(renderRect.w), &(renderRect.h));
    renderRect.x = 0;
    renderRect.y = 0;
}

void BackgroundRenderComponent::update()
{
    renderRect.y = gameEntity->position.y;
    SDL_RenderCopyEx(windowElements->renderer, sprite, NULL, &renderRect, 0.0, NULL, SDL_FLIP_NONE);
    renderRect.y = gameEntity->position.y - renderRect.h;
    SDL_RenderCopyEx(windowElements->renderer, sprite, NULL, &renderRect, 0.0, NULL, SDL_FLIP_NONE);
}

BackgroundRenderComponent::~BackgroundRenderComponent()
{
     SDL_DestroyTexture(sprite);
     sprite=NULL;
}
