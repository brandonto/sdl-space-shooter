/*******************************************************************//*
 * Implementation of the MenuState class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-08-10
 *********************************************************************/
#include <SDL2/SDL.h>
#include "MenuState.h"
#include "ApplicationStateManager.h"
#include "../WindowElements.h"

MenuState::MenuState(ApplicationStateManager* applicationStateManager,
                     WindowElements* windowElements)
{
    this->applicationStateManager = applicationStateManager;
    this->windowElements = windowElements;
}

MenuState::~MenuState()
{
    // To be implemented
}

void MenuState::onEnter()
{
    //
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
    SDL_FillRect(windowElements->surface, NULL,
                 SDL_MapRGB(windowElements->surface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(windowElements->window);
    SDL_Delay(2000);
}

void MenuState::onExit()
{

}
