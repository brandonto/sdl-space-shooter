/*******************************************************************//*
 * Implementation of the Application class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-09-06
 *********************************************************************/
#include "Application.h"

#include <cstdio>
#include <cstddef>
#include <SDL2/SDL.h>
#include "ApplicationStateManager.h"
#include "SDL_util.h"

// Constructor
Application::Application()
:   applicationStateManager(NULL)
{
    windowElements.window = NULL;
    windowElements.renderer = NULL;
}

// Destructor
Application::~Application()
{
    if (applicationStateManager!=NULL) { delete applicationStateManager; }
}

int Application::start()
{
    if (!initialize())
    {
        return -1;
    }

    while (!applicationStateManager->isExitState())
    {
        fpsManager.beginFrame();
        applicationStateManager->onEvent();
        applicationStateManager->onUpdate();
        applicationStateManager->changeState();
        applicationStateManager->onRender();
        fpsManager.endFrame();
    }

    terminate();

    return 0;
}

bool Application::initialize()
{
    // Initializes all SDL modules
    if (!SDL_util::initialize())
    {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    windowElements.window = SDL_CreateWindow(
        "Space Shooter",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        windowElements.WINDOW_WIDTH,
        windowElements.WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (windowElements.window == NULL)
    {
        printf("Could not create SDL_Window: %s\n", SDL_GetError());
        return false;
    }


    windowElements.renderer = SDL_CreateRenderer(windowElements.window, -1, SDL_RENDERER_ACCELERATED);
    if (windowElements.renderer == NULL)
    {
        printf("Could not create SDL_Renderer: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(windowElements.renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    applicationStateManager = new ApplicationStateManager(&windowElements);

    return true;
}

void Application::terminate()
{

    SDL_DestroyRenderer(windowElements.renderer);
    windowElements.renderer = NULL;

    SDL_DestroyWindow(windowElements.window);
    windowElements.window = NULL;

    SDL_util::terminate();
}
