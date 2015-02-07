/*******************************************************************//*
 * Implementation of the MeteorRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-14
 * @modified    2015-02-06
 *********************************************************************/
#include "MeteorRenderComponent.h"

#include <cstddef>
#include "GameEntity.h"
#include "SDL_util.h"
#include "WindowElements.h"

MeteorRenderComponent::MeteorRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;

    texture = new Texture(windowElements);
    texture->setTexture("bin/graphics/sprites/meteorBrown_big1.png");

    gameEntity->position.x = -1000; // Put the meteor off the screen
    gameEntity->position.y = -1000;

    renderRect.w = texture->getSpriteWidth();
    renderRect.h = texture->getSpriteHeight();
    texture->setAngle(0);
}

void MeteorRenderComponent::update()
{
    renderRect.x = gameEntity->position.x - texture->getSpriteWidth()/2;
    renderRect.y = gameEntity->position.y - texture->getSpriteHeight()/2;
    SDL_RenderCopyEx(windowElements->renderer, texture->getTexture(), NULL, &renderRect, texture->getAngle(), NULL, SDL_FLIP_NONE);
}

MeteorRenderComponent::~MeteorRenderComponent()
{
    delete texture;
}
