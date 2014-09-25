/*******************************************************************//*
 * Implementation of the ExplosionRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-25
 * @modified    2014-09-25
 *********************************************************************/
#include "ExplosionRenderComponent.h"

#include <cstddef>
#include "GameEntity.h"
#include "SDL_util.h"
#include "WindowElements.h"

ExplosionRenderComponent::ExplosionRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements,
                                               GameEntity* destroyedEntity)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    sprite = SDL_util::create_texture_from_image(windowElements, "bin/graphics/sprites/explosion.png");
    SDL_QueryTexture(sprite, NULL, NULL, &spriteWidth, &spriteHeight);
    renderRect.w = destroyedEntity->getRenderComponent()->spriteWidth;
    renderRect.h = destroyedEntity->getRenderComponent()->spriteHeight;
    gameEntity->position.x = destroyedEntity->position.x;
    gameEntity->position.y = destroyedEntity->position.y;
    renderRect.x = gameEntity->position.x - renderRect.w/2;
    renderRect.y = gameEntity->position.y - renderRect.h/2;
}

void ExplosionRenderComponent::update()
{
    SDL_RenderCopy(windowElements->renderer, sprite, NULL, &renderRect);
}

ExplosionRenderComponent::~ExplosionRenderComponent()
{
    SDL_DestroyTexture(sprite);
    sprite=NULL;
}
