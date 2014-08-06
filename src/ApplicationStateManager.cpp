#include "ApplicationStateManager.h"
#include "app-states/ApplicationState.h"

/*******************************************************************//*
 * Implementation of the ApplicationStateManager class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-08-05
 *********************************************************************/

ApplicationStateManager::ApplicationStateManager()
{
    currentState = new IntroState();
}

ApplicationStateManager::~ApplicationStateManager()
{
    // TBD
}

ApplicationState* ApplicationStateManager::getCurrentState()
{
    return currentState;
}

/*private*/ void ApplicationStateManager::setNextState()
{
    nextStateEnum = nextState;
}
