/*******************************************************************//*
 * Implementation of the EnemyRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-17
 * @modified    2015-02-18
 *********************************************************************/
#include "EnemyRenderComponent.h"

#include <cstddef>
#include "GameEntity.h"
#include "SDL_util.h"
#include "Texture.h"
#include "Util.h"
#include "WindowElements.h"

EnemyRenderComponent::EnemyRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;

    texture = new Texture(windowElements);
    texture->setTexture(Util::fix_path("../data/graphics/sprites/enemyBlack1.png"));

    gameEntity->position.x = windowElements->WINDOW_WIDTH/2;
    gameEntity->position.y = -0.2*windowElements->WINDOW_HEIGHT;
    renderRect.w = texture->getSpriteWidth();
    renderRect.h = texture->getSpriteHeight();
}

void EnemyRenderComponent::update()
{
    renderRect.x = gameEntity->position.x - renderRect.w/2;
    renderRect.y = gameEntity->position.y - renderRect.h/2;
    SDL_RenderCopy(windowElements->renderer, texture->getTexture(), NULL, &renderRect);
}

EnemyRenderComponent::~EnemyRenderComponent()
{
    delete texture;
}
