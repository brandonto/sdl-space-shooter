/*******************************************************************//*
 * Implementation of the GameState class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-05
 * @modified    2014-09-14
 *********************************************************************/
#include "GameState.h"

#include <SDL2/SDL.h>
#include "ApplicationStateManager.h"
#include "GameEntity.h"
#include "WindowElements.h"

GameState::GameState(ApplicationStateManager* applicationStateManager,
                     WindowElements* windowElements)
:   nextState(0), blackScreen(windowElements), gameEntityManager(windowElements)
{
    this->applicationStateManager = applicationStateManager;
    this->windowElements = windowElements;
}

GameState::~GameState()
{

}

void GameState::onEnter()
{
    blackScreen.startBlackIn();
    background = gameEntityManager.createBackground();
    player = gameEntityManager.createPlayer();
    meteor = gameEntityManager.createMeteor();
}

void GameState::onEvent()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            applicationStateManager->setNextState(STATE_EXIT);
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.scancode)
            {
                case SDL_SCANCODE_ESCAPE:
                    stateTransition(STATE_MENU);
                    break;

                case SDL_SCANCODE_P:
                    applicationStateManager->pushStateOnStack(STATE_PAUSE);
                    break;
            }
        }
        gameEntityManager.onEvent(&event);
    }
}

void GameState::onUpdate()
{
    if (blackScreen.isBlackingIn())
    {
        blackScreen.onUpdate();
        if (!blackScreen.isBlackingIn())
        {
            //Do something when black in is done
        }
    }
    else if (blackScreen.isBlackingOut())
    {
        blackScreen.onUpdate();
        if (!blackScreen.isBlackingOut())
        {
            applicationStateManager->setNextState(nextState);
        }
    }
    gameEntityManager.onUpdate();
}

void GameState::onRender()
{
    gameEntityManager.onRender();
}

void GameState::onExit()
{

}

void GameState::stateTransition(int nextState)
{
    blackScreen.startBlackOut();
    this->nextState = nextState;
}
