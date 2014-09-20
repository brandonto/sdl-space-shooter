/*******************************************************************//*
 * Implementation of the EnemyProjectileRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-17
 * @modified    2014-09-19
 *********************************************************************/
#include "EnemyProjectileRenderComponent.h"

#include <cstddef>
#include "GameEntity.h"
#include "EnemyRenderComponent.h"
#include "SDL_util.h"
#include "WindowElements.h"

EnemyProjectileRenderComponent::EnemyProjectileRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements,
                                               GameEntity* enemyEntity)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    sprite = SDL_util::create_texture_from_image(windowElements, "bin/graphics/sprites/laserRed03.png");
    SDL_QueryTexture(sprite, NULL, NULL, &spriteWidth, &spriteHeight);
    renderRect.w = spriteWidth;
    renderRect.h = spriteHeight;
    gameEntity->position.x = enemyEntity->position.x;
    gameEntity->position.y = enemyEntity->position.y + dynamic_cast<EnemyRenderComponent*>(enemyEntity->getRenderComponent())->spriteHeight/2 - spriteHeight/2;
}

void EnemyProjectileRenderComponent::update()
{
    renderRect.x = gameEntity->position.x - spriteWidth/2;
    renderRect.y = gameEntity->position.y - spriteHeight/2;
    SDL_RenderCopy(windowElements->renderer, sprite, NULL, &renderRect);
}

EnemyProjectileRenderComponent::~EnemyProjectileRenderComponent()
{
    SDL_DestroyTexture(sprite);
    sprite=NULL;
}
