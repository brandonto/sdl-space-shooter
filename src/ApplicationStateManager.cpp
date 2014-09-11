/*******************************************************************//*
 * Implementation of the ApplicationStateManager class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-09-10
 *********************************************************************/
#include "ApplicationStateManager.h"

#include <cassert>
#include <cstddef>
#include <SDL2/SDL.h>
#include "ApplicationState.h"
#include "GameState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "WindowElements.h"

//Constructors
ApplicationStateManager::ApplicationStateManager(WindowElements* windowElements)
:   windowElements(windowElements), currentStateEnum(STATE_MENU),
    nextStateEnum(STATE_NULL), pushedStateEnum(STATE_NULL), popState(false)
{
    currentState = new MenuState(this, windowElements);
    stateStack.push_back(currentState);
    stateStackEnum.push_back(currentStateEnum);
    currentState->onEnter();
}

//Destructors
ApplicationStateManager::~ApplicationStateManager()
{
    //if (currentState != NULL)
    //{
    //    delete currentState;
    //    currentState = NULL;
    //}
    while (stateStack.size() > 0)
    {
        delete stateStack.back();
        stateStack.pop_back();
        //for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
         //   delete stateStack[i];
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
    SDL_RenderClear(windowElements->renderer);
    if (stateStack.size() == 1)
    {
        currentState->onRender();
    }
    else
    {
        std::vector<ApplicationState*>::iterator it;
        for (it = stateStack.begin(); it != stateStack.end(); it++)
        {
            (*it)->onRender();
        }
    }
    SDL_RenderPresent(windowElements->renderer);
}

ApplicationState* ApplicationStateManager::getCurrentState()
{
    return currentState;
}

bool ApplicationStateManager::isExitState()
{
    return currentStateEnum == STATE_EXIT;
}

void ApplicationStateManager::setNextState(int nextState)
{
    nextStateEnum = nextState;
}

void ApplicationStateManager::pushStateOnStack(int pushedState)
{
    pushedStateEnum = pushedState;
}

void ApplicationStateManager::popStateOnStack()
{
    popState = true;
}

void ApplicationStateManager::changeState()
{
    if (nextStateEnum != STATE_NULL)
    {
        if (nextStateEnum != STATE_EXIT)
        {
            assert(stateStack.size() == stateStackEnum.size());
            while (stateStackEnum.size() > 0)
            {
                stateStack.back()->onExit();
                delete stateStack.back();
                stateStack.pop_back();
                stateStackEnum.pop_back();
                currentState = NULL;
            }
        }

        switch (nextStateEnum)
        {
            case STATE_GAME:
                currentState = new GameState(this, windowElements);
                currentState->onEnter();
                stateStack.push_back(currentState);
                stateStackEnum.push_back(nextStateEnum);
                break;

            case STATE_MENU:
                currentState = new MenuState(this, windowElements);
                currentState->onEnter();
                stateStack.push_back(currentState);
                stateStackEnum.push_back(nextStateEnum);
                break;
        }

        currentStateEnum = nextStateEnum;
        nextStateEnum = STATE_NULL;
    }
    else if (pushedStateEnum != STATE_NULL)
    {
        switch (pushedStateEnum)
        {
            case STATE_PAUSE:
                currentState = new PauseState(this, windowElements);
                currentState->onEnter();
                stateStack.push_back(currentState);
                currentStateEnum = pushedStateEnum;
                stateStackEnum.push_back(pushedStateEnum);
                break;
        }

        pushedStateEnum = STATE_NULL;
    }
    else if (popState)
    {
        if (stateStack.size() > 1)
        {
            stateStack.back()->onExit();
            delete stateStack.back();
            stateStack.pop_back();
            stateStackEnum.pop_back();
            currentState = stateStack.back();
            currentStateEnum = stateStackEnum.back();
        }

        popState = false;
    }
}
