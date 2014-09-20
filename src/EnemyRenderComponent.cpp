/*******************************************************************//*
 * Implementation of the EnemyRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-17
 * @modified    2014-09-19
 *********************************************************************/
#include "EnemyRenderComponent.h"

#include <cstddef>
#include "GameEntity.h"
#include "SDL_util.h"
#include "WindowElements.h"

EnemyRenderComponent::EnemyRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    sprite = SDL_util::create_texture_from_image(windowElements, "bin/graphics/sprites/enemyBlack1.png");
    SDL_QueryTexture(sprite, NULL, NULL, &spriteWidth, &spriteHeight);
    gameEntity->position.x = windowElements->WINDOW_WIDTH/2;
    gameEntity->position.y = -0.2*windowElements->WINDOW_HEIGHT;
    renderRect.w = spriteWidth;
    renderRect.h = spriteHeight;
}

void EnemyRenderComponent::update()
{
    renderRect.x = gameEntity->position.x - spriteWidth/2;
    renderRect.y = gameEntity->position.y - spriteHeight/2;
    SDL_RenderCopy(windowElements->renderer, sprite, NULL, &renderRect);
}

EnemyRenderComponent::~EnemyRenderComponent()
{
    SDL_DestroyTexture(sprite);
    sprite=NULL;
}
