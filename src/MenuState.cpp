/*******************************************************************//*
 * Implementation of the MenuState class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-09-01
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
:   fadeIn(true), fadeOut(false), menuAlpha(0)
{
    this->applicationStateManager = applicationStateManager;
    this->windowElements = windowElements;
}

MenuState::~MenuState()
{
    //
}

void MenuState::onEnter()
{
    background = gameEntityManager.createBackground(windowElements);
    mainMenu = gameEntityManager.createMainMenu(windowElements);
}

void MenuState::onEvent()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            applicationStateManager->setNextState(STATE_EXIT);
        }
        gameEntityManager.onEvent(event);
    }
}

void MenuState::onUpdate()
{
    if (fadeIn)
    {
        if (menuAlpha<255)
        {
            menuAlpha+=5;
            if (menuAlpha==255) { fadeIn = false; }
        }
        dynamic_cast<UIPanelRenderComponent*>(mainMenu[0]->getRenderComponent())->setAlphaBlend(menuAlpha);
    }
    else if (fadeOut)
    {
        if (menuAlpha>0)
        {
            menuAlpha-=5;
            if (menuAlpha==0) { fadeOut = false; }
        }
        dynamic_cast<UIPanelRenderComponent*>(mainMenu[0]->getRenderComponent())->setAlphaBlend(menuAlpha);
    }
}

void MenuState::onRender()
{
    SDL_RenderClear(windowElements->renderer);
    gameEntityManager.onRender();
    SDL_RenderPresent(windowElements->renderer);
    //SDL_FillRect(windowElements->surface, NULL,
    //             SDL_MapRGB(windowElements->surface->format, 0xFF, 0xFF, 0xFF));
    //SDL_UpdateWindowSurface(windowElements->window);
    SDL_Delay(50);
}

void MenuState::onExit()
{

}
