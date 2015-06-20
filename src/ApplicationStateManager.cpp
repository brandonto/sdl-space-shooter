/*******************************************************************//*
 * Implementation of the ApplicationStateManager class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2015-02-20
 *********************************************************************/
#include "ApplicationStateManager.h"

#include <cassert>
#include <cstddef>

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
	#include <SDL2/SDL.h>
#endif

#include "ApplicationState.h"
#include "CreditsState.h"
#include "InstructionsState.h"
#include "GameOverState.h"
#include "GameState.h"
#include "GameMenuState.h"
#include "MenuState.h"
#include "OptionsState.h"
#include "PauseState.h"
#include "VictoryState.h"
#include "WindowElements.h"

// Constructors
ApplicationStateManager::ApplicationStateManager(WindowElements* windowElements)
:   windowElements(windowElements), currentStateEnum(STATE_MENU),
    nextStateEnum(STATE_NULL), pushedStateEnum(STATE_NULL), popState(false)
{

    // Creates a menu state and pushes it onto the state stack, the game starts in the menu
    // state
    currentState = new MenuState(this, windowElements);
    stateStack.push_back(currentState);
    stateStackEnum.push_back(currentStateEnum);
    currentState->onEnter();
}

// Destructors
ApplicationStateManager::~ApplicationStateManager()
{
    while (stateStack.size() > 0)
    {
        delete stateStack.back();
        stateStack.pop_back();
    }
}

// Methods
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
    // Clear rendering window
    SDL_RenderClear(windowElements->renderer);

    // If there is only one state on the state stack, then render that one state
    if (stateStack.size() == 1)
    {
        currentState->onRender();
    }
    // If there are more than one state on the state stack, they are rendered in order
    // (the most recent state will be rendered last)
    else
    {
        std::vector<ApplicationState*>::iterator it;
        for (it = stateStack.begin(); it != stateStack.end(); it++)
        {
            (*it)->onRender();
        }
    }

    // Updates the sceen with the new rendered content
    SDL_RenderPresent(windowElements->renderer);
}

// Returns the current state that the game is in
ApplicationState* ApplicationStateManager::getCurrentState()
{
    return currentState;
}

// Returns the first state on the state stack
ApplicationState* ApplicationStateManager::getMainState()
{
    return *(stateStack.begin());
}

// Returns a boolean indicating whether the game is in an exit state
bool ApplicationStateManager::isExitState()
{
    return currentStateEnum == STATE_EXIT;
}

// Sets the next state to be switched to when changeState() is called. Usually at
// the end of the current frame
void ApplicationStateManager::setNextState(int nextState)
{
    nextStateEnum = nextState;
}

// Pushes a state onto the top of the state stack when changeState() is called. Usually at
// the end of the current frame
void ApplicationStateManager::pushStateOnStack(int pushedState)
{
    pushedStateEnum = pushedState;
}

// Pops a state off the top of the state stack when changeState() is called. Usually at the
// end of the current frame
void ApplicationStateManager::popStateOnStack()
{
    popState = true;
}

// Make any changes to the state. Usually called at the end of the frame
void ApplicationStateManager::changeState()
{
    // This conditional branch is entered if setNextState() has been called
    if (nextStateEnum != STATE_NULL)
    {
        // Pops everything off of the state stack before changing states
        if (nextStateEnum != STATE_EXIT)
        {
            // Assert is here to check if the state stack and state enumeration stack sizes
            // agree before popping everything to avoid a null pointer exception
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

        // Switches to correct enumerated state and calls its enter functions
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

        // Updates current state enumeration
        currentStateEnum = nextStateEnum;
        // Nullify for next frame
        nextStateEnum = STATE_NULL;
    }
    // This conditional branch is entered if pushStateOnStack() has been called
    else if (pushedStateEnum != STATE_NULL)
    {
        // Pushes a state onto the state stack. This allows a sub-state transition
        // effect
        switch (pushedStateEnum)
        {
            case STATE_CREDITS:
                currentState = new CreditsState(this, windowElements);
                currentState->onEnter();
                stateStack.push_back(currentState);
                stateStackEnum.push_back(nextStateEnum);
                break;

            case STATE_GAMEMENU:
                currentState = new GameMenuState(this, windowElements);
                currentState->onEnter();
                stateStack.push_back(currentState);
                currentStateEnum = pushedStateEnum;
                stateStackEnum.push_back(pushedStateEnum);
                break;

            case STATE_GAMEOVER:
                currentState = new GameOverState(this, windowElements);
                currentState->onEnter();
                stateStack.push_back(currentState);
                currentStateEnum = pushedStateEnum;
                stateStackEnum.push_back(pushedStateEnum);
                break;

            case STATE_INSTRUCTIONS:
                currentState = new InstructionsState(this, windowElements);
                currentState->onEnter();
                stateStack.push_back(currentState);
                stateStackEnum.push_back(nextStateEnum);
                break;

            case STATE_OPTIONS:
                currentState = new OptionsState(this, windowElements);
                currentState->onEnter();
                stateStack.push_back(currentState);
                currentStateEnum = pushedStateEnum;
                stateStackEnum.push_back(pushedStateEnum);
                break;

            case STATE_PAUSE:
                currentState = new PauseState(this, windowElements);
                currentState->onEnter();
                stateStack.push_back(currentState);
                currentStateEnum = pushedStateEnum;
                stateStackEnum.push_back(pushedStateEnum);
                break;

            case STATE_VICTORY:
                currentState = new VictoryState(this, windowElements);
                currentState->onEnter();
                stateStack.push_back(currentState);
                currentStateEnum = pushedStateEnum;
                stateStackEnum.push_back(pushedStateEnum);
                break;
        }

        // Nullify for next frame
        pushedStateEnum = STATE_NULL;
    }
    // This conditional branch is entered if popStateOnStack() has been called
    else if (popState)
    {
        // Ensure that the state stack has a state before popping
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
