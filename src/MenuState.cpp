/*******************************************************************//*
 * Implementation of the MenuState class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-09-06
 *********************************************************************/
#include "MenuState.h"

#include <SDL2/SDL.h>
#include "ApplicationStateManager.h"
#include "GameEntity.h"
#include "RenderComponent.h"
#include "UIPanelRenderComponent.h"
#include "WindowElements.h"

MenuState::MenuState(ApplicationStateManager* applicationStateManager,
                     WindowElements* windowElements)
:   fadeIn(false), fadeOut(false), menuAlpha(0),
    nextState(0), blackScreen(windowElements)
{
    this->applicationStateManager = applicationStateManager;
    this->windowElements = windowElements;
}

MenuState::~MenuState()
{
}

void MenuState::onEnter()
{
    blackScreen.startBlackIn();
    background = gameEntityManager.createBackground(windowElements);
    mainMenu = gameEntityManager.createMainMenu(windowElements, this);

    for (int i=0; i<mainMenu.size(); i++)
    {
        dynamic_cast<UIPanelRenderComponent*>(mainMenu[i]->getRenderComponent())->setAlphaBlend(menuAlpha);
    }
}

void MenuState::onEvent()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            applicationStateManager->setNextState(STATE_EXIT);
        }
        gameEntityManager.onEvent(&event);
    }
}

void MenuState::onUpdate()
{
    if (fadeIn)
    {
        if (menuAlpha<200)
        {
            menuAlpha+=10;
            if (menuAlpha==200) { fadeIn = false; }
        }
        for (int i=0; i<mainMenu.size(); i++)
        {
            dynamic_cast<UIPanelRenderComponent*>(mainMenu[i]->getRenderComponent())->setAlphaBlend(menuAlpha);
        }
    }
    else if (fadeOut)
    {
        if (menuAlpha>0)
        {
            menuAlpha-=10;
            if (menuAlpha==0) { fadeOut = false; blackScreen.startBlackOut(); }
        }
        for (int i=0; i<mainMenu.size(); i++)
        {
            dynamic_cast<UIPanelRenderComponent*>(mainMenu[i]->getRenderComponent())->setAlphaBlend(menuAlpha);
        }
    }
    else if (blackScreen.isBlackingIn())
    {
        blackScreen.onUpdate();
        if (!blackScreen.isBlackingIn())
        {
            fadeIn = true;
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

void MenuState::onRender()
{
    SDL_RenderClear(windowElements->renderer);
    gameEntityManager.onRender();
    blackScreen.onRender();
    SDL_RenderPresent(windowElements->renderer);
    //SDL_Delay(50);
}

void MenuState::onExit()
{

}

void MenuState::stateTransition(int nextState)
{
    this->nextState = nextState;
    fadeOut = true;
}
