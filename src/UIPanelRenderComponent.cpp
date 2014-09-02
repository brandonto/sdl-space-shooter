/*******************************************************************//*
 * Render component for UI panel
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-28
 * @modified    2014-09-01
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
    windowElements(windowElements)
{
    spriteSurface = SDL_util::create_surface_from_image("bin/graphics/ui/glassPanel.png");
    sprite = SDL_util::create_texture_from_surface(windowElements, spriteSurface);
}

void UIPanelRenderComponent::update(GameEntity* gameEntity)
{
    SDL_RenderCopy(windowElements->renderer, sprite, NULL, &renderRect);
}

void UIPanelRenderComponent::enableBlending()
{
    SDL_SetTextureBlendMode(sprite, SDL_BLENDMODE_BLEND);
}

void UIPanelRenderComponent::setAlphaBlend(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(sprite, alpha);
}

void UIPanelRenderComponent::setRenderRect(SDL_Rect* rect)
{
    renderRect = *rect;
}

void UIPanelRenderComponent::addText(std::string text, int fontSize, SDL_Rect* destRect)
{
    SDL_Surface* surface = NULL;

    SDL_Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    surface = SDL_util::create_surface_from_text("bin/font/kenvector_future.ttf", text,
                                                fontSize, &color);
    sprite = SDL_util::create_texture_from_surfaces(windowElements, surface, NULL, spriteSurface,
                                                    destRect);
}

UIPanelRenderComponent::~UIPanelRenderComponent()
{
    SDL_FreeSurface(spriteSurface);
    SDL_DestroyTexture(sprite);
    spriteSurface=NULL;
    sprite=NULL;
}
