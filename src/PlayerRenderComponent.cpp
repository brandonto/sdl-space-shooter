/*******************************************************************//*
 * Implementation of the PlayerRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2014-09-06
 *********************************************************************/
#include "PlayerRenderComponent.h"

#include <cstddef>
#include "GameEntity.h"
#include "SDL_util.h"
#include "WindowElements.h"

PlayerRenderComponent::PlayerRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements)
:   sprite(NULL),
    gameEntity(gameEntity),
    windowElements(windowElements)
{
    sprite = SDL_util::create_texture_from_image(windowElements, "bin/graphics/sprites/playerShip1_blue.png");
    SDL_QueryTexture(sprite, NULL, NULL, &spriteWidth, &spriteHeight);
    gameEntity->xPos = windowElements->WINDOW_WIDTH/2;
    gameEntity->yPos = 0.8*windowElements->WINDOW_HEIGHT;
    renderRect.w = spriteWidth;
    renderRect.h = spriteHeight;
}

void PlayerRenderComponent::update()
{
    renderRect.x = gameEntity->xPos - spriteWidth/2;
    renderRect.y = gameEntity->yPos - spriteHeight/2;
    SDL_RenderCopy(windowElements->renderer, sprite, NULL, &renderRect);
}

PlayerRenderComponent::~PlayerRenderComponent()
{
    SDL_DestroyTexture(sprite);
    sprite=NULL;
}
