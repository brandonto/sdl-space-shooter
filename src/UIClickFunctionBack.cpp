/*******************************************************************//*
 * Implementation of the UIClickFunctionBack class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-01
 * @modified    2015-02-01
 *********************************************************************/
#include "UIClickFunctionBack.h"

#include "ApplicationState.h"

UIClickFunctionBack::UIClickFunctionBack(ApplicationState* state)
:   state(state)
{

}

void UIClickFunctionBack::onClick()
{
    state->stateTransition(STATE_MENU);
}
