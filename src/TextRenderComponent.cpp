/*******************************************************************//*
 * Implementation of the TextRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-01-31
 * @modified    2015-02-01
 *********************************************************************/
#include "TextRenderComponent.h"

#include <cstddef>
#include "GameEntity.h"
#include "SDL_util.h"
#include "WindowElements.h"

TextRenderComponent::TextRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements)
:   alpha(0),
    cachedAlpha(0)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    sprite = NULL;
}

void TextRenderComponent::update()
{
    if (sprite != NULL)
    {
        SDL_RenderCopy(windowElements->renderer, sprite, NULL, &renderRect);
    }
}

// Enables alpha blending effect on texture
void TextRenderComponent::enableBlending()
{
    SDL_SetTextureBlendMode(sprite, SDL_BLENDMODE_BLEND);
}

// Sets the alpha value of the texture
void TextRenderComponent::setAlphaBlend(Uint8 alpha)
{
    this->alpha = alpha;
    SDL_SetTextureAlphaMod(sprite, alpha);
}

// Returns the alpha value of the texture
Uint8 TextRenderComponent::getAlphaBlend()
{
    return alpha;
}

// Sets the SDL_Rect to render to
void TextRenderComponent::setRenderRect(SDL_Rect* rect)
{
    renderRect = *rect;
}

void TextRenderComponent::setText(std::string text, int fontSize)
{
    SDL_Color color;
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = 0xFF;
    if (sprite != NULL)
    {
        SDL_DestroyTexture(sprite);
    }
    sprite = SDL_util::create_texture_from_text(windowElements, "bin/font/kenpixel_square.ttf",
                text, fontSize, &color);
}

TextRenderComponent::~TextRenderComponent()
{
    SDL_DestroyTexture(sprite);
    sprite=NULL;
}
