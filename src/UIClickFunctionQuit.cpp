/*******************************************************************//*
 * This class encapsulates a function called on UI Quit click
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-05
 * @modified    2014-09-05
 *********************************************************************/
#include "UIClickFunctionQuit.h"

#include "ApplicationState.h"
#include "ApplicationStateManager.h"

UIClickFunctionQuit::UIClickFunctionQuit(ApplicationStateManager* stateManager)
:   stateManager(stateManager)
{

}

void UIClickFunctionQuit::onClick()
{
    stateManager->setNextState(STATE_EXIT);
}
