/*******************************************************************//*
 * Implementation of the GameMenuState class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-02
 * @modified    2015-02-16
 *********************************************************************/
#include "GameMenuState.h"

#include <SDL2/SDL.h>
#include "ApplicationStateManager.h"
#include "GameEntity.h"
#include "GameState.h"
#include "PauseState.h"
#include "RenderComponent.h"
#include "SDL_util.h"
#include "WindowElements.h"

GameMenuState::GameMenuState(ApplicationStateManager* applicationStateManager,
                     WindowElements* windowElements)
:   fadeIn(true),
    fadeOut(false),
    menuAlpha(0),
    nextState(0),
    transitioningStates(false),
    gameEntityManager(windowElements,this),
    blackScreen(windowElements)
{
    this->applicationStateManager = applicationStateManager;
    this->windowElements = windowElements;
    this->stateEnum = STATE_GAMEMENU;
    this->xmlPath = "../data/xml/states/GameMenuState.xml";
}

GameMenuState::~GameMenuState()
{

}

void GameMenuState::onEnter()
{
    blackScreen.setAlphaBlend(0);
    uiEntities = gameEntityManager.getFactory()->createUIEntities();
}

void GameMenuState::onEvent()
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
                    onExit();
                    break;
            }
        }
        gameEntityManager.onEvent(&event);
    }
}

void GameMenuState::onUpdate()
{
    if (fadeIn)
    {
        if (menuAlpha<200)
        {
            menuAlpha+=10;
            if (menuAlpha==200) { fadeIn = false; }
        }
        for (int i=0; i<uiEntities.size(); i++)
        {
            uiEntities[i]->getRenderComponent()->getTexture()->setAlphaBlend(menuAlpha);
        }
    }
    else if (fadeOut)
    {
        if (menuAlpha>0)
        {
            menuAlpha-=10;
            if (menuAlpha==0)
            {
                fadeOut = false;
                if (transitioningStates)
                {
                    blackScreen.startBlackOut();
                }
                else
                {
                    applicationStateManager->popStateOnStack();
                    dynamic_cast<GameState*>(applicationStateManager->getMainState())->setPauseStatus(UNPAUSED_THIS_FRAME);
                }
            }
        }
        for (int i=0; i<uiEntities.size(); i++)
        {
            uiEntities[i]->getRenderComponent()->getTexture()->setAlphaBlend(menuAlpha);
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

void GameMenuState::onRender()
{
    gameEntityManager.onRender();
    blackScreen.onRender();
}

void GameMenuState::onExit()
{
    fadeOut = true;
}

void GameMenuState::stateTransition(int nextState)
{
    this->nextState = nextState;
    fadeOut = true;
    transitioningStates = true;
}
