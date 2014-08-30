/*******************************************************************//*
 * Render component for UI title
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-28
 * @modified    2014-08-30
 *********************************************************************/
#include "UITitleRenderComponent.h"

#include <cstddef>
#include "GameEntity.h"
#include "SDL_util.h"
#include "WindowElements.h"

UITitleRenderComponent::UITitleRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements)
:   sprite(NULL),
    //renderRect(NULL),
    windowElements(windowElements)
{
    sprite=SDL_util::load_image(windowElements, "bin/graphics/ui/glassPanel.png");
    gameEntity->xPos = windowElements->WINDOW_WIDTH/5;
    gameEntity->yPos = windowElements->WINDOW_HEIGHT/12;
    renderRect.x = gameEntity->xPos;
    renderRect.y = gameEntity->yPos;
    renderRect.w = windowElements->WINDOW_WIDTH - 2*gameEntity->xPos;
    renderRect.h = windowElements->WINDOW_HEIGHT - 9*gameEntity->yPos;
}

void UITitleRenderComponent::update(GameEntity* gameEntity)
{
    SDL_RenderCopy(windowElements->renderer, sprite, NULL, &renderRect);
}

UITitleRenderComponent::~UITitleRenderComponent()
{
    SDL_DestroyTexture(sprite);
    sprite=NULL;
}
