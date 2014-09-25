/*******************************************************************//*
 * Implementation of the PlayerProjectileRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-08
 * @modified    2014-09-25
 *********************************************************************/
#include "PlayerProjectileRenderComponent.h"

#include <cstddef>
#include "GameEntity.h"
#include "SDL_util.h"
#include "WindowElements.h"

PlayerProjectileRenderComponent::PlayerProjectileRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements,
                                               GameEntity* playerEntity)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    sprite = SDL_util::create_texture_from_image(windowElements, "bin/graphics/sprites/laserBlue03.png");
    SDL_QueryTexture(sprite, NULL, NULL, &spriteWidth, &spriteHeight);
    renderRect.w = spriteWidth;
    renderRect.h = spriteHeight;
    gameEntity->position.x = playerEntity->position.x;
    gameEntity->position.y = playerEntity->position.y - playerEntity->getRenderComponent()->spriteHeight/2 - spriteHeight/2;
}

void PlayerProjectileRenderComponent::update()
{
    renderRect.x = gameEntity->position.x - spriteWidth/2;
    renderRect.y = gameEntity->position.y - spriteHeight/2;
    SDL_RenderCopy(windowElements->renderer, sprite, NULL, &renderRect);
}

PlayerProjectileRenderComponent::~PlayerProjectileRenderComponent()
{
    SDL_DestroyTexture(sprite);
    sprite=NULL;
}
