/*******************************************************************//*
 * Implementation of the ExplosionRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-25
 * @modified    2015-02-21
 *********************************************************************/
#include "ExplosionRenderComponent.h"

#include <cstddef>
#include "GameEntity.h"
#include "SDL_util.h"
#include "Texture.h"
#include "Util.h"
#include "WindowElements.h"

ExplosionRenderComponent::ExplosionRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;

    texture = new Texture(windowElements);
    //texture->setTexture(Util::fix_path("../data/graphics/sprites/explosionSpritesheet.png"));

    // Stretches to fit render destination
    //renderRect.w = destroyedEntity->getRenderComponent()->getTexture()->getSpriteWidth();
    //renderRect.h = destroyedEntity->getRenderComponent()->getTexture()->getSpriteHeight();

    // Calculates position of sprite
    //gameEntity->position.x = destroyedEntity->position.x;
    //gameEntity->position.y = destroyedEntity->position.y;
    //renderRect.x = gameEntity->position.x - renderRect.w/2;
    //renderRect.y = gameEntity->position.y - renderRect.h/2;

    // Sets partition spritesheet
    //texture->partitionSpritesheet(Util::fix_path("../data/xml/spritesheets/explosionSpritesheet.xml"));

    // Start at the first animation frame
    //texture->setAnimationFrame(0);
}

void ExplosionRenderComponent::update()
{
    SDL_Rect sourceRect = texture->getSourceRect();
    SDL_RenderCopy(windowElements->renderer, texture->getTexture(), &sourceRect, &renderRect);
}

// Returns false if at end of animation
bool ExplosionRenderComponent::advanceAnimation()
{
    return texture->advanceAnimation();
}

ExplosionRenderComponent::~ExplosionRenderComponent()
{
    delete texture;
}
