#include <stdio.h>
#include <SDL2/SDL.h>
#include "Application.h"

/*******************************************************************//*
 * Implementation of the Application class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-08-05
 *********************************************************************/

//
// Constructor
//
Application::Application()
{
    gameWindow = NULL;
    gameScreen = NULL;
}

Application::~Application()
{
    SDL_DestroyWindow(gameWindow);
}

int Application::start()
{
    // Initializes all SDL modules
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return -1;
    }

    gameWindow = SDL_CreateWindow(
        "Space Shooter",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        768,
        SDL_WINDOW_SHOWN
    );

    if (gameWindow == NULL)
    {
        printf("Could not create SDL_Window: %s\n", SDL_GetError());
        return -1;
    }

    gameScreen = SDL_GetWindowSurface(gameWindow);

    SDL_FillRect(gameScreen, NULL, SDL_MapRGB(gameScreen->format, 0xFF, 0xFF, 0xFF));

    SDL_UpdateWindowSurface(gameWindow);

    SDL_Delay(5000);

    // Start main menu
    //Menu menu = Menu();

    return 0;
}
