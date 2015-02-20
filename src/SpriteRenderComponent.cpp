/*******************************************************************//*
 * Implementation of the SpriteRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-01
 * @modified    2015-02-20
 *********************************************************************/
#include "SpriteRenderComponent.h"

#include <cstddef>
#include "GameEntity.h"
#include "SDL_util.h"
#include "Texture.h"
#include "WindowElements.h"

SpriteRenderComponent::SpriteRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements)
:   timedSprite(false)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;

    texture = new Texture(windowElements);
}

void SpriteRenderComponent::update()
{
    if (renderEnabled)
    {
        if (texture->getTexture() != NULL)
        {
            SDL_RenderCopy(windowElements->renderer, texture->getTexture(), NULL, &renderRect);
        }

        if (timedSprite)
        {
            if (timer.getTimeOnTimer()>activeTime)
            {
                gameEntity->remove = true;
            }
        }
    }
}

// Sets the SDL_Rect to render to
void SpriteRenderComponent::setRenderRect(SDL_Rect* rect)
{
    renderRect = *rect;
}

void SpriteRenderComponent::setActiveTimer(int msec)
{
    timedSprite = true;
    activeTime = msec;
    timer.start();
}

SpriteRenderComponent::~SpriteRenderComponent()
{
    delete texture;
}
