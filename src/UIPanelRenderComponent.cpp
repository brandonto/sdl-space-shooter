/*******************************************************************//*
 * Implementation of the UIPanelRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-28
 * @modified    2015-02-18
 *********************************************************************/
#include "UIPanelRenderComponent.h"

#include <cstddef>
#include "GameEntity.h"
#include "SDL_util.h"
#include "Texture.h"
#include "Util.h"
#include "WindowElements.h"

UIPanelRenderComponent::UIPanelRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements)
:   cachedAlpha(0),
    selected(false)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;

    texture = new Texture(windowElements);
    texture->setTexture(Util::fix_path("../data/graphics/ui/glassPanel.png"));
}

void UIPanelRenderComponent::update()
{
    if (texture->getTexture() != NULL)
    {
        SDL_RenderCopy(windowElements->renderer, texture->getTexture(), NULL, &renderRect);
    }
}

bool UIPanelRenderComponent::isSelected()
{
    return selected;
}

void UIPanelRenderComponent::toggleSelected()
{
    if (!selected)
    {
        cachedAlpha = texture->getAlphaBlend();
        texture->setAlphaBlend(OPAQUE);
        selected = true;
    }
    else
    {
        texture->setAlphaBlend(cachedAlpha);
        selected = false;
    }
}

bool UIPanelRenderComponent::buttonReady()
{
    return texture->getAlphaBlend()>=200;
}

UIPanelRenderComponent::~UIPanelRenderComponent()
{
    delete texture;
}
