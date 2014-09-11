/*******************************************************************//*
 * Implementation of the PauseState class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-10
 * @modified    2014-09-10
 *********************************************************************/
#include "PauseState.h"

#include <SDL2/SDL.h>
#include "ApplicationStateManager.h"
#include "SDL_util.h"
#include "WindowElements.h"

PauseState::PauseState(ApplicationStateManager* applicationStateManager,
                     WindowElements* windowElements)
:   pausedText(NULL)
{
    this->applicationStateManager = applicationStateManager;
    this->windowElements = windowElements;
}

PauseState::~PauseState()
{

}

void PauseState::onEnter()
{
    SDL_Color color;
    color.r = 150;
    color.g = 150;
    color.b = 255;
    color.a = 255;
    pausedText = SDL_util::create_texture_from_text(windowElements,
                                                "bin/font/kenvector_future.ttf",
                                                "PAUSED", 72, &color);
    SDL_SetTextureBlendMode(pausedText, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(pausedText, 200);
    int width, height;
    SDL_QueryTexture(pausedText, NULL, NULL, &width, &height);
    pausedTextRect.x = windowElements->WINDOW_WIDTH/2 - width/2;
    pausedTextRect.y = windowElements->WINDOW_HEIGHT/2 - height/2;
    pausedTextRect.w = width;
    pausedTextRect.h = height;
}

void PauseState::onEvent()
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
                    applicationStateManager->popStateOnStack();
                    break;

                case SDL_SCANCODE_P:
                    applicationStateManager->popStateOnStack();
                    break;
            }
        }
    }
}

void PauseState::onUpdate()
{

}

void PauseState::onRender()
{
    //SDL_RenderClear(windowElements->renderer);
    SDL_RenderCopy(windowElements->renderer, pausedText, NULL, &pausedTextRect);
    //SDL_RenderPresent(windowElements->renderer);
}

void PauseState::onExit()
{

}
