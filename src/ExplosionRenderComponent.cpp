/*******************************************************************//*
 * Implementation of the ExplosionRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-25
 * @modified    2014-10-21
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
    sprite = SDL_util::create_texture_from_image(windowElements, "bin/graphics/sprites/explosionspritesheet.png");

    //Spritesheet is 4 by 4
    SDL_QueryTexture(sprite, NULL, NULL, &spriteWidth, &spriteHeight);
    spriteWidth /= 4;
    spriteHeight /= 4;

    //Stretches to fit render destination
    renderRect.w = destroyedEntity->getRenderComponent()->spriteWidth;
    renderRect.h = destroyedEntity->getRenderComponent()->spriteHeight;

    //Calculates position of sprite
    gameEntity->position.x = destroyedEntity->position.x;
    gameEntity->position.y = destroyedEntity->position.y;
    renderRect.x = gameEntity->position.x - renderRect.w/2;
    renderRect.y = gameEntity->position.y - renderRect.h/2;

    //Sets partition spritesheet
    for (int i=0; i<16; i++)
    {
        srcRectArray[i].w = spriteWidth;
        srcRectArray[i].h = spriteHeight;
        srcRectArray[i].x = i%4 * spriteWidth;
        srcRectArray[i].y = i/4 * spriteHeight;
    }

    animationIndex = 0;
    srcRect = srcRectArray[animationIndex];
}

void ExplosionRenderComponent::update()
{

    SDL_RenderCopy(windowElements->renderer, sprite, &srcRect, &renderRect);
}

//Returns false if at end of animation
bool ExplosionRenderComponent::advanceAnimation()
{
    if (++animationIndex < 16)
    {
        srcRect = srcRectArray[animationIndex];
        return true;
    }
    return false;
}

ExplosionRenderComponent::~ExplosionRenderComponent()
{
    SDL_DestroyTexture(sprite);
    sprite=NULL;
}
