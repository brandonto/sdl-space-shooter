/*******************************************************************//*
 * Implementation of the BackgroundRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-17
 * @modified    2015-02-19
 *********************************************************************/
#include "BackgroundRenderComponent.h"

#include <cstddef>

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
	#include <SDL2/SDL.h>
#endif

#include "GameEntity.h"
#include "SDL_util.h"
#include "Texture.h"
#include "Util.h"
#include "WindowElements.h"

BackgroundRenderComponent::BackgroundRenderComponent(GameEntity* gameEntity,
                                                    WindowElements* windowElements)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;

    texture = new Texture(windowElements);
    SDL_Texture* sprite = SDL_util::create_background_texture(windowElements, Util::fix_path("../data/graphics/background/darkPurple.png"));
    texture->setTexture(sprite);
    sprite = NULL;

    //SDL_QueryTexture(sprite, NULL, NULL, &(renderRect.w), &(renderRect.h));
    renderRect.x = 0;
    renderRect.y = 0;
    renderRect.w = texture->getSpriteWidth();
    renderRect.h = texture->getSpriteHeight();
}

void BackgroundRenderComponent::update()
{
    renderRect.y = gameEntity->position.y;
    SDL_RenderCopyEx(windowElements->renderer, texture->getTexture(), NULL, &renderRect, 0.0, NULL, SDL_FLIP_NONE);
    renderRect.y = gameEntity->position.y - renderRect.h;
    SDL_RenderCopyEx(windowElements->renderer, texture->getTexture(), NULL, &renderRect, 0.0, NULL, SDL_FLIP_NONE);
}

BackgroundRenderComponent::~BackgroundRenderComponent()
{
    delete texture;
}
