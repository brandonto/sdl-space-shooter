/*******************************************************************//*
 * Implementation of the UIPanelRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-28
 * @modified    2014-09-06
 *********************************************************************/
#include "UIPanelRenderComponent.h"

#include <cstddef>
#include "GameEntity.h"
#include "SDL_util.h"
#include "WindowElements.h"

UIPanelRenderComponent::UIPanelRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements)
:   sprite(NULL),
    gameEntity(gameEntity),
    windowElements(windowElements),
    alpha(0),
    cachedAlpha(0),
    selected(false)
{
    spriteSurface = SDL_util::create_surface_from_image("bin/graphics/ui/glassPanel.png");
    sprite = SDL_util::create_texture_from_surface(windowElements, spriteSurface);
}

void UIPanelRenderComponent::update()
{
    SDL_RenderCopy(windowElements->renderer, sprite, NULL, &renderRect);
}

void UIPanelRenderComponent::enableBlending()
{
    SDL_SetTextureBlendMode(sprite, SDL_BLENDMODE_BLEND);
}

void UIPanelRenderComponent::setAlphaBlend(Uint8 alpha)
{
    this->alpha = alpha;
    SDL_SetTextureAlphaMod(sprite, alpha);
}

Uint8 UIPanelRenderComponent::getAlphaBlend()
{
    return alpha;
}

bool UIPanelRenderComponent::isSelected()
{
    return selected;
}

void UIPanelRenderComponent::toggleSelected()
{
    if (!selected)
    {
        cachedAlpha = alpha;
        setAlphaBlend(SELECTED_ALPHA);
        selected = true;
    }
    else
    {
        setAlphaBlend(cachedAlpha);
        selected = false;
    }
}

void UIPanelRenderComponent::setRenderRect(SDL_Rect* rect)
{
    renderRect = *rect;
    //Uint32 format;
    //SDL_QueryTexture(sprite, &format, NULL, NULL, NULL);
    //SDL_Texture* newTexture = SDL_CreateTexture(windowElements->renderer,
    //                                            //format,
    //                                            SDL_PIXELFORMAT_RGBA8888,
    //                                            SDL_TEXTUREACCESS_TARGET,
    //                                            rect->w, rect->h);
    //SDL_SetRenderTarget(windowElements->renderer, newTexture);
    //SDL_RenderCopy(windowElements->renderer, sprite, NULL, NULL);
    //SDL_SetRenderTarget(windowElements->renderer, NULL);
    //SDL_DestroyTexture(sprite);
    //SDL_DestroyTexture(newTexture);
    //sprite = newTexture;
}

SDL_Rect* UIPanelRenderComponent::getRenderRect()
{
    return &renderRect;
}

void UIPanelRenderComponent::addText(std::string text, int fontSize, SDL_Rect* destRect,
                                        bool scaled)
{
    SDL_Surface* surface = NULL;

    SDL_Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    surface = SDL_util::create_surface_from_text("bin/font/kenvector_future_thin.ttf", text,
                                                fontSize, &color);
    SDL_DestroyTexture(sprite);
    sprite = SDL_util::create_texture_from_surfaces(windowElements, surface, NULL,
                                                    spriteSurface, destRect, scaled);
    SDL_FreeSurface(surface);
}

//void UIPanelRenderComponent::addText(std::string text, int fontSize, SDL_Rect* destRect,
//                                        bool scaled)
//{
//    Uint32 format;
//    int w, h;
//    SDL_QueryTexture(sprite, &format, NULL, &w, &h);
//    SDL_Texture* newTexture = SDL_CreateTexture(windowElements->renderer,
//                                                format,
//                                                //SDL_PIXELFORMAT_RGBA8888,
//                                                SDL_TEXTUREACCESS_TARGET,
//                                                w, h);
//    SDL_Texture* texture = NULL;
//
//    SDL_Color color;
//    color.r = 255;
//    color.g = 255;
//    color.b = 255;
//    color.a = 255;
//    texture = SDL_util::create_texture_from_text(windowElements,
//                                                "bin/font/kenvector_future_thin.ttf", text,
//                                                //"bin/font/kenvector_future.ttf", text,
//                                                fontSize, &color);
//    SDL_SetRenderTarget(windowElements->renderer, newTexture);
//    SDL_RenderCopy(windowElements->renderer, sprite, NULL, NULL);
//    SDL_RenderCopy(windowElements->renderer, texture, NULL, destRect);
//    SDL_SetRenderTarget(windowElements->renderer, NULL);
//    SDL_DestroyTexture(sprite);
//    SDL_DestroyTexture(texture);
//    //SDL_DestroyTexture(newTexture);
//    sprite = newTexture;
//}

bool UIPanelRenderComponent::buttonReady()
{
    return alpha>=200;
}

UIPanelRenderComponent::~UIPanelRenderComponent()
{
    SDL_FreeSurface(spriteSurface);
    SDL_DestroyTexture(sprite);
    spriteSurface=NULL;
    sprite=NULL;
}
