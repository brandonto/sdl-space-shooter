/*******************************************************************//*
 * Implementation of the PlayerRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2015-02-01
 *********************************************************************/
#include "PlayerRenderComponent.h"

#include <cstddef>
#include "GameEntity.h"
#include "SDL_util.h"
#include "Texture.h"
#include "WindowElements.h"

PlayerRenderComponent::PlayerRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;

    texture = new Texture(windowElements);
    texture->setTexture("bin/graphics/sprites/playerShip1_blue.png");

    gameEntity->position.x = windowElements->WINDOW_WIDTH/2;
    gameEntity->position.y = 0.8*windowElements->WINDOW_HEIGHT;
    renderRect.w = texture->getSpriteWidth();
    renderRect.h = texture->getSpriteHeight();
}

void PlayerRenderComponent::update()
{
    renderRect.x = gameEntity->position.x - texture->getSpriteWidth()/2;
    renderRect.y = gameEntity->position.y - texture->getSpriteHeight()/2;
    SDL_RenderCopy(windowElements->renderer, texture->getTexture(), NULL, &renderRect);
}

// Enables alpha blending effect on texture
void PlayerRenderComponent::enableBlending()
{
    texture->enableAlphaBlend();
}

// Sets the alpha value of the texture
void PlayerRenderComponent::setAlphaBlend(Uint8 alpha)
{
    texture->setAlphaBlend(alpha);
}

// Returns the alpha value of the texture
Uint8 PlayerRenderComponent::getAlphaBlend()
{
    return texture->getAlphaBlend();
}

PlayerRenderComponent::~PlayerRenderComponent()
{
    delete texture;
}
