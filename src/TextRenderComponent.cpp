/*******************************************************************//*
 * Implementation of the TextRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-01-31
 * @modified    2015-02-18
 *********************************************************************/
#include "TextRenderComponent.h"

#include <cstddef>
#include "GameEntity.h"
#include "SDL_util.h"
#include "Texture.h"
#include "Util.h"
#include "WindowElements.h"

TextRenderComponent::TextRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;

    texture = new Texture(windowElements);
}

void TextRenderComponent::update()
{
    if (texture->getTexture() != NULL)
    {
        SDL_RenderCopy(windowElements->renderer, texture->getTexture(), NULL, &renderRect);
    }
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
    SDL_Texture* sprite = SDL_util::create_texture_from_text(windowElements,
                                Util::fix_path("../data/font/kenpixel_square.ttf"),
                                                            text,
                                                            fontSize,
                                                            &color);
    texture->setTexture(sprite);
    sprite = NULL;
}

TextRenderComponent::~TextRenderComponent()
{
    delete texture;
}
