/*******************************************************************//*
 * Implementation of the MenuState class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-09-05
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
    blackIn(true), blackOut(false), blackScreenAlpha(255),
    nextState(0)
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
    Uint32 rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif
    SDL_Surface* blackScreenSurface = SDL_CreateRGBSurface(0, windowElements->WINDOW_WIDTH,
                                                        windowElements->WINDOW_HEIGHT, 32,
                                                        rmask, gmask, bmask, amask);
    SDL_FillRect(blackScreenSurface, NULL,
                 SDL_MapRGB(blackScreenSurface->format, 0x00, 0x00, 0x00));
    blackScreen = SDL_CreateTextureFromSurface(windowElements->renderer, blackScreenSurface);
    SDL_FreeSurface(blackScreenSurface);
    SDL_SetTextureBlendMode(blackScreen, SDL_BLENDMODE_BLEND);

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
            if (menuAlpha==0) { fadeOut = false; blackOut = true; }
        }
        for (int i=0; i<mainMenu.size(); i++)
        {
            dynamic_cast<UIPanelRenderComponent*>(mainMenu[i]->getRenderComponent())->setAlphaBlend(menuAlpha);
        }
    }
    else if (blackIn)
    {
        if (blackScreenAlpha>0)
        {
            if ( blackScreenAlpha == 15 ) { blackScreenAlpha = 0; }
            else { blackScreenAlpha-=80; }
            if ( blackScreenAlpha == 0 ) { blackIn = false; fadeIn = true; }
            SDL_SetTextureAlphaMod(blackScreen, blackScreenAlpha);
        }
    }
    else if (blackOut)
    {
        if (blackScreenAlpha<255)
        {
            if ( blackScreenAlpha == 240 ) { blackScreenAlpha = 255; }
            else { blackScreenAlpha+=80; }
            if ( blackScreenAlpha == 255 )
            {
                blackOut = false;
                applicationStateManager->setNextState(nextState);
            }
            SDL_SetTextureAlphaMod(blackScreen, blackScreenAlpha);
        }
    }
}

void MenuState::onRender()
{
    SDL_RenderClear(windowElements->renderer);
    gameEntityManager.onRender();
    SDL_RenderCopy(windowElements->renderer, blackScreen, NULL, NULL);
    SDL_RenderPresent(windowElements->renderer);
    //SDL_FillRect(windowElements->surface, NULL,
    //             SDL_MapRGB(windowElements->surface->format, 0xFF, 0xFF, 0xFF));
    //SDL_UpdateWindowSurface(windowElements->window);
    SDL_Delay(50);
}

void MenuState::onExit()
{

}

void MenuState::stateTransition(int nextState)
{
    this->nextState = nextState;
    fadeOut = true;
}
