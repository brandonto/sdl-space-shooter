/*******************************************************************//*
 * Implementation of the UIClickFunctionResume class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-02
 * @modified    2015-02-02
 *********************************************************************/
#include "UIClickFunctionResume.h"

#include "ApplicationState.h"

UIClickFunctionResume::UIClickFunctionResume(ApplicationState* state)
:   state(state)
{

}

void UIClickFunctionResume::onClick()
{
    state->onExit();
}


