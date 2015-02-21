/*******************************************************************//*
 * Implementation of the EnemyProjectileRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-17
 * @modified    2015-02-21
 *********************************************************************/
#include "EnemyProjectileRenderComponent.h"

#include <cstddef>
#include "GameEntity.h"
#include "RenderComponent.h"
#include "SDL_util.h"
#include "Util.h"
#include "WindowElements.h"

EnemyProjectileRenderComponent::EnemyProjectileRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;

    texture = new Texture(windowElements);
    texture->setTexture(Util::fix_path("../data/graphics/sprites/laserRed03.png"));

    //renderRect.w = texture->getSpriteWidth();
    //renderRect.h = texture->getSpriteHeight();
    //gameEntity->position.x = enemyEntity->position.x;
    //gameEntity->position.y = enemyEntity->position.y
    //    + (enemyEntity->getRenderComponent()->getTexture()->getSpriteHeight())/2
    //    - (texture->getSpriteHeight())/2;
}

void EnemyProjectileRenderComponent::update()
{
    renderRect.x = gameEntity->position.x - renderRect.w/2;
    renderRect.y = gameEntity->position.y - renderRect.h/2;
    SDL_RenderCopy(windowElements->renderer, texture->getTexture(), NULL, &renderRect);
}

EnemyProjectileRenderComponent::~EnemyProjectileRenderComponent()
{
    delete texture;
}
