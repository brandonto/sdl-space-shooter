/*******************************************************************//*
 * Implementation of the PlayerProjectileRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-08
 * @modified    2015-02-21
 *********************************************************************/
#include "PlayerProjectileRenderComponent.h"

#include <cstddef>
#include "GameEntity.h"
#include "SDL_util.h"
#include "Texture.h"
#include "Util.h"
#include "WindowElements.h"

PlayerProjectileRenderComponent::PlayerProjectileRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;

    texture = new Texture(windowElements);
    texture->setTexture(Util::fix_path("../data/graphics/sprites/laserBlue03.png"));

    //renderRect.w = texture->getSpriteWidth();
    //renderRect.h = texture->getSpriteHeight();
    //gameEntity->position.x = playerEntity->position.x;
    //gameEntity->position.y = playerEntity->position.y - (playerEntity->getRenderComponent()->getTexture()->getSpriteHeight())/2 - (texture->getSpriteHeight())/2;
}

void PlayerProjectileRenderComponent::update()
{
    renderRect.x = gameEntity->position.x - texture->getSpriteWidth()/2;
    renderRect.y = gameEntity->position.y - texture->getSpriteHeight()/2;
    SDL_RenderCopy(windowElements->renderer, texture->getTexture(), NULL, &renderRect);
}

PlayerProjectileRenderComponent::~PlayerProjectileRenderComponent()
{
    delete texture;
}
