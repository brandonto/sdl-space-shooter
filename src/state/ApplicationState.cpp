#include "ApplicationState.h"

/*******************************************************************//*
 * Default implementation of virtual methods in ApplicationState class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-08-06
 *********************************************************************/

ApplicationState::~ApplicationState()
{
    return;
}

void ApplicationState::onEnter()
{
    return;
}

//ApplicationState::OnEvent() must be implemented in subclass

//ApplicationState::OnUpdate() must be implemented in subclass

//ApplicationState::OnExit() must be implemented in subclass

void ApplicationState::onExit()
{
    return;
}
