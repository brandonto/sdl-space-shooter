/*******************************************************************//*
 * Implementation of the UIClickFunctionMenu class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-02
 * @modified    2015-02-02
 *********************************************************************/
#include "UIClickFunctionMenu.h"

#include "ApplicationState.h"

UIClickFunctionMenu::UIClickFunctionMenu(ApplicationState* state)
:   state(state)
{

}

void UIClickFunctionMenu::onClick()
{
    state->stateTransition(STATE_MENU);
}

