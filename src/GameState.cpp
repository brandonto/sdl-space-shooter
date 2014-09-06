/*******************************************************************//*
 * Implementation of the GameState class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-05
 * @modified    2014-09-05
 *********************************************************************/
#include "GameState.h"

#include <SDL2/SDL.h>
#include "ApplicationStateManager.h"
#include "GameEntity.h"
#include "WindowElements.h"

GameState::GameState(ApplicationStateManager* applicationStateManager,
                     WindowElements* windowElements)
:   nextState(0), blackScreen(windowElements)
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
    background = gameEntityManager.createBackground(windowElements);
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
            if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                stateTransition(STATE_MENU);
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
}

void GameState::onRender()
{
    SDL_RenderClear(windowElements->renderer);
    gameEntityManager.onRender();
    SDL_RenderPresent(windowElements->renderer);
    SDL_Delay(50);
}

void GameState::onExit()
{

}

void GameState::stateTransition(int nextState)
{
    blackScreen.startBlackOut();
    this->nextState = nextState;
}
