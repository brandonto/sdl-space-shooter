/*******************************************************************//*
 * Implementation of the UIPanelInputComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-03
 * @modified    2015-02-08
 *********************************************************************/
#include "UIPanelInputComponent.h"

#include "GameEntity.h"
#include "UIClickFunction.h"
#include "UIPanelRenderComponent.h"

UIPanelInputComponent::UIPanelInputComponent(GameEntity* gameEntity)
:   clickFunction(NULL),
    render(NULL),
    buttonPressedDown(false)
{
    this->gameEntity = gameEntity;
    render = dynamic_cast<UIPanelRenderComponent*>(gameEntity->getRenderComponent());
}

UIPanelInputComponent::~UIPanelInputComponent()
{
    if (clickFunction!=NULL) { delete clickFunction; }
}

void UIPanelInputComponent::update(SDL_Event* event)
{
    //Synchronizes render rect with UIPanelRenderComponent
    uiRect = render->getRenderRect();
    //printf("x=%d y=%d w=%d h=%d\n", uiRect.x, uiRect.y, uiRect.w, uiRect.h);

    if (event->type == SDL_MOUSEMOTION)
    {
        //If the mouse moves inside the button
        if (event->motion.x >= uiRect.x && event->motion.x <= uiRect.x+uiRect.w &&
            event->motion.y >= uiRect.y && event->motion.y <= uiRect.y+uiRect.h)
        {
            if (!render->isSelected() && render->buttonReady())
            {
                render->toggleSelected();
                //Element should now be selected
            }
        }
        else
        {
            if (render->isSelected() && render->buttonReady())
            {
                render->toggleSelected();
                //Element should now be unselected
            }
            if (clickFunction!=NULL && buttonPressedDown)
            {
                buttonPressedDown = false;
            }
        }
    }
    else if (clickFunction!=NULL && event->type == SDL_MOUSEBUTTONDOWN)
    {
        if (render->isSelected())
        {
            buttonPressedDown = true;
        }
    }
    else if (clickFunction!=NULL && event->type == SDL_MOUSEBUTTONUP && buttonPressedDown)
    {
        if (render->isSelected())
        {
            clickFunction->onClick();
        }
        buttonPressedDown = false;
    }
}

void UIPanelInputComponent::addClickFunction(UIClickFunction* clickFunction)
{
    this->clickFunction = clickFunction;
}
