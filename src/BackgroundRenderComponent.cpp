/*******************************************************************//*
 * Render component for background
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-17
 * @modified    2014-08-20
 *********************************************************************/
#include "BackgroundRenderComponent.h"

#include <SDL2/SDL.h>
#include "SDL_util.h"

BackgroundRenderComponent::BackgroundRenderComponent(SDL_Renderer* renderer)
:   sprite(NULL),
    renderer(renderer)
{
    sprite=SDL_util::load_image(renderer, "../bin/graphics/background/purple.png");
}

void BackgroundRenderComponent::update(GameEntity* gameEntity)
{
    SDL_RenderCopy(renderer, sprite, NULL, NULL);
}

BackgroundRenderComponent::~BackgroundRenderComponent()
{
     SDL_DestroyTexture(sprite);
     sprite=NULL;
}
