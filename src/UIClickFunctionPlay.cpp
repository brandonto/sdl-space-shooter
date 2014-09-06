/*******************************************************************//*
 * Implementation of the UIClickFunctionPlay class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-05
 * @modified    2014-09-05
 *********************************************************************/
#include "UIClickFunctionPlay.h"

#include "ApplicationState.h"

UIClickFunctionPlay::UIClickFunctionPlay(ApplicationState* state)
:   state(state)
{

}

void UIClickFunctionPlay::onClick()
{
    state->stateTransition(STATE_GAME);
}
