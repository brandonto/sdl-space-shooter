/*******************************************************************//*
 * Implementation of the MenuState class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-08-20
 *********************************************************************/
#include "MenuState.h"

#include <SDL2/SDL.h>
#include "ApplicationStateManager.h"
#include "WindowElements.h"

MenuState::MenuState(ApplicationStateManager* applicationStateManager,
                     WindowElements* windowElements)
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
    gameEntityManager.createBackground(windowElements->renderer);
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
    // To be implemented
}

void MenuState::onRender()
{
    SDL_RenderClear(windowElements->renderer);
    gameEntityManager.onRender();
    SDL_RenderPresent(windowElements->renderer);
    //SDL_FillRect(windowElements->surface, NULL,
    //             SDL_MapRGB(windowElements->surface->format, 0xFF, 0xFF, 0xFF));
    //SDL_UpdateWindowSurface(windowElements->window);
    SDL_Delay(500);
}

void MenuState::onExit()
{

}
