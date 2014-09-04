/*******************************************************************//*
 * Input component for UI panel
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-03
 * @modified    2014-09-03
 *********************************************************************/
#include "UIPanelInputComponent.h"

#include "GameEntity.h"
#include "UIPanelRenderComponent.h"

UIPanelInputComponent::UIPanelInputComponent(GameEntity* gameEntity)
:   gameEntity(gameEntity)
{
    render = dynamic_cast<UIPanelRenderComponent*>(gameEntity->getRenderComponent());
    uiRect = render->getRenderRect();
}

UIPanelInputComponent::~UIPanelInputComponent()
{

}

void UIPanelInputComponent::update(SDL_Event* event)
{
    if (event->type == SDL_MOUSEMOTION)
    {
        if (event->motion.x >= uiRect->x && event->motion.x <= uiRect->x+uiRect->w &&
            event->motion.y >= uiRect->y && event->motion.y <= uiRect->y+uiRect->h)
        {
            if (!render->isSelected() && render->buttonReady())
            {
                render->toggleSelected();
            }
        }
        else
        {
            if (render->isSelected() && render->buttonReady())
            {
                render->toggleSelected();
            }
        }
    }
}
