/*******************************************************************//*
 * Default implementation of virtual methods in ApplicationState class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2015-02-07
 *********************************************************************/
#include "ApplicationState.h"

#include "ApplicationStateManager.h"
#include "WindowElements.h"

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

void ApplicationState::stateTransition(int nextState)
{
    applicationStateManager->setNextState(nextState);
}

int ApplicationState::getStateEnum()
{
    return stateEnum;
}

void ApplicationState::setXmlPath(std::string xmlPath)
{
    this->xmlPath = xmlPath;
}

std::string ApplicationState::getXmlPath()
{
    return xmlPath;
}
