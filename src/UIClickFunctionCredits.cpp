/*******************************************************************//*
 * Implementation of the UIClickFunctionCredits class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-01
 * @modified    2015-02-01
 *********************************************************************/
#include "UIClickFunctionCredits.h"

#include "ApplicationState.h"

UIClickFunctionCredits::UIClickFunctionCredits(ApplicationState* state)
:   state(state)
{

}

void UIClickFunctionCredits::onClick()
{
    state->stateTransition(STATE_CREDITS);
}
