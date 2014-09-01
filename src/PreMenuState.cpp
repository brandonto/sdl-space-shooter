/*******************************************************************//*
 * Implementation of the PreMenuState class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-31
 * @modified    2014-08-31
 *********************************************************************/
#include "PreMenuState.h"

#include <SDL2/SDL.h>
#include "ApplicationStateManager.h"
#include "WindowElements.h"

PreMenuState::PreMenuState(ApplicationStateManager* applicationStateManager,
                           WindowElements* windowElements)
{
    this->applicationStateManager = applicationStateManager;
    this->windowElements = windowElements;
}

PreMenuState::~PreMenuState()
{
    //
}

void PreMenuState::onEnter()
{
    gameEntityManager.createBackground(windowElements);
    gameEntityManager.createMainMenu(windowElements, PRE_MENU);
}

void PreMenuState::onEvent()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            applicationStateManager->setNextState(STATE_EXIT);
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            if (event.button == SDL_BUTTON_LEFT)
            {
                applicationStateManager->setNextState(STATE_MENU);
            }
        }
        gameEntityManager.onEvent(event);
    }
}

void PreMenuState::onUpdate()
{
    // To be implemented
}

void PreMenuState::onRender()
{
    SDL_RenderClear(windowElements->renderer);
    gameEntityManager.onRender();
    SDL_RenderPresent(windowElements->renderer);
    //SDL_FillRect(windowElements->surface, NULL,
    //             SDL_MapRGB(windowElements->surface->format, 0xFF, 0xFF, 0xFF));
    //SDL_UpdateWindowSurface(windowElements->window);
    SDL_Delay(50);
}

void PreMenuState::onExit()
{

}
