/*******************************************************************//*
 * Implementation of the SpriteRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-01
 * @modified    2015-02-01
 *********************************************************************/
#include "SpriteRenderComponent.h"

#include <cstddef>
#include "GameEntity.h"
#include "SDL_util.h"
#include "WindowElements.h"

SpriteRenderComponent::SpriteRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements)
:   alpha(0), cachedAlpha(0)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
}

void SpriteRenderComponent::update()
{
    SDL_RenderCopy(windowElements->renderer, sprite, NULL, &renderRect);
}

// Enables alpha blending effect on texture
void SpriteRenderComponent::enableBlending()
{
    SDL_SetTextureBlendMode(sprite, SDL_BLENDMODE_BLEND);
}

// Sets the alpha value of the texture
void SpriteRenderComponent::setAlphaBlend(Uint8 alpha)
{
    this->alpha = alpha;
    SDL_SetTextureAlphaMod(sprite, alpha);
}

// Returns the alpha value of the texture
Uint8 SpriteRenderComponent::getAlphaBlend()
{
    return alpha;
}

// Sets the SDL_Rect to render to
void SpriteRenderComponent::setRenderRect(SDL_Rect* rect)
{
    renderRect = *rect;
}

void SpriteRenderComponent::setImage(std::string path)
{
    if (sprite != NULL)
    {
        SDL_DestroyTexture(sprite);
    }
    sprite = SDL_util::create_texture_from_image(windowElements, path);
}

SpriteRenderComponent::~SpriteRenderComponent()
{
    SDL_DestroyTexture(sprite);
    sprite=NULL;
}
