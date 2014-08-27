/*******************************************************************//*
 * Implementation of the ApplicationStateManager class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-08-26
 *********************************************************************/
#include "ApplicationStateManager.h"

#include <cstddef>
#include <SDL2/SDL.h>
#include "ApplicationState.h"
#include "MenuState.h"
#include "WindowElements.h"

//Constructors
ApplicationStateManager::ApplicationStateManager(WindowElements* windowElements)
    : windowElements(windowElements)
{
    //currentState = new IntroState();
    //currentState = new PreMenuTransitionState();
    currentState = new MenuState(this, windowElements);
    currentState->onEnter();
    nextStateEnum = STATE_NULL;
}

//Destructors
ApplicationStateManager::~ApplicationStateManager()
{
    if (currentState != NULL)
    {
        delete currentState;
        currentState = NULL;
    }
}

//Methods
void ApplicationStateManager::onEvent()
{
    currentState->onEvent();
}

void ApplicationStateManager::onUpdate()
{
    currentState->onUpdate();
}

void ApplicationStateManager::onRender()
{
    currentState->onRender();
}

ApplicationState* ApplicationStateManager::getCurrentState()
{
    return currentState;
}

bool ApplicationStateManager::isExitState()
{
    return nextStateEnum == STATE_EXIT;
}

void ApplicationStateManager::setNextState(int nextState)
{
    nextStateEnum = nextState;
}

void ApplicationStateManager::changeState()
{
    if (nextStateEnum != STATE_NULL)
    {
        if (nextStateEnum != STATE_EXIT)
        {
            currentState->onExit();
            delete currentState;
            currentState = NULL;
        }

        switch (nextStateEnum)
        {
            case STATE_MENU:
                currentState = new MenuState(this, windowElements);
                currentState->onEnter();
                break;

            case STATE_GAME:
                break;
        }
    }
}

