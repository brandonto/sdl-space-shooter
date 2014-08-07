#include <stdio.h>
#include <SDL2/SDL.h>
#include "Application.h"
#include "WindowElements.h"
#include "states/ApplicationStateManager.h"

/*******************************************************************//*
 * Implementation of the Application class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-08-06
 *********************************************************************/

// Constructor
Application::Application()
{
    windowElements.window = NULL;
    windowElements.surface = NULL;
    applicationStateManager = NULL;
    quit = false
}

// Destructor
Application::~Application()
{
    SDL_DestroyWindow(windowElements.window);
}

int Application::start()
{
    if (!initialize())
    {
        return -1;
    }

    while (!applicationStateManager.isExit())
    {
        applicationStateManager->onEvent();
        applicationStateManager->onUpdate();
        applicationStateManager->onRender();
    }

    if (!terminate())
    {
        return -1;
    }

    return 0;
}

bool Application::initialize()
{
    // Initializes all SDL modules
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    windowElements.window = SDL_CreateWindow(
        "Space Shooter",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        768,
        SDL_WINDOW_SHOWN
    );

    if (windowElements.window == NULL)
    {
        printf("Could not create SDL_Window: %s\n", SDL_GetError());
        return false;
    }

    windowElements.surface = SDL_Getsurface(windowElements.window);

    applicationStateManager = new ApplicationStateManager(&windowElements);

    return true;
}

bool Application::terminate()
{
    delete applicationStateManager;

    SDL_FreeSurface(windowElements.surface);
    windowElements.surface = NULL;

    SDL_DestroyWindow(windowElements.window);
    windowElements.window = NULL;

    return true;
}
