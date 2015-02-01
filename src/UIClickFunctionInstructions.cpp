/*******************************************************************//*
 * Implementation of the UIClickFunctionInstructions class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-01-31
 * @modified    2015-01-31
 *********************************************************************/
#include "UIClickFunctionInstructions.h"

#include "ApplicationState.h"

UIClickFunctionInstructions::UIClickFunctionInstructions(ApplicationState* state)
:   state(state)
{

}

void UIClickFunctionInstructions::onClick()
{
    state->stateTransition(STATE_INSTRUCTIONS);
}
