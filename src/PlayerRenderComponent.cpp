/*******************************************************************//*
 * Implementation of the PlayerRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2014-09-12
 *********************************************************************/
#include "PlayerRenderComponent.h"

#include <cstddef>
#include "GameEntity.h"
#include "SDL_util.h"
#include "WindowElements.h"

PlayerRenderComponent::PlayerRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    sprite = SDL_util::create_texture_from_image(windowElements, "bin/graphics/sprites/playerShip1_blue.png");
    SDL_QueryTexture(sprite, NULL, NULL, &spriteWidth, &spriteHeight);
    gameEntity->position.x = windowElements->WINDOW_WIDTH/2;
    gameEntity->position.y = 0.8*windowElements->WINDOW_HEIGHT;
    renderRect.w = spriteWidth;
    renderRect.h = spriteHeight;
}

void PlayerRenderComponent::update()
{
    renderRect.x = gameEntity->position.x - spriteWidth/2;
    renderRect.y = gameEntity->position.y - spriteHeight/2;
    SDL_RenderCopy(windowElements->renderer, sprite, NULL, &renderRect);
}

PlayerRenderComponent::~PlayerRenderComponent()
{
    SDL_DestroyTexture(sprite);
    sprite=NULL;
}
