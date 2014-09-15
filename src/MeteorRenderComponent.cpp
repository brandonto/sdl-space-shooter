/*******************************************************************//*
 * Implementation of the MeteorRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-14
 * @modified    2014-09-14
 *********************************************************************/
#include "MeteorRenderComponent.h"

#include <cstddef>
#include "GameEntity.h"
#include "SDL_util.h"
#include "WindowElements.h"

MeteorRenderComponent::MeteorRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements)
:   sprite(NULL),
    gameEntity(gameEntity),
    windowElements(windowElements),
    angle(0)
{
    sprite = SDL_util::create_texture_from_image(windowElements, "bin/graphics/sprites/meteorBrown_big1.png");
    SDL_QueryTexture(sprite, NULL, NULL, &spriteWidth, &spriteHeight);
    gameEntity->position.x = -1000;
    gameEntity->position.y = -1000;
    renderRect.w = spriteWidth;
    renderRect.h = spriteHeight;
}

void MeteorRenderComponent::update()
{
    renderRect.x = gameEntity->position.x - spriteWidth/2;
    renderRect.y = gameEntity->position.y - spriteHeight/2;
    SDL_RenderCopyEx(windowElements->renderer, sprite, NULL, &renderRect, angle, NULL, SDL_FLIP_NONE);
}

MeteorRenderComponent::~MeteorRenderComponent()
{
    SDL_DestroyTexture(sprite);
    sprite=NULL;
}
