/*******************************************************************//*
 * Structure of useful SDL window variables. 
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-06
 * @modified    2014-08-10
 *********************************************************************/
#ifndef _WINDOWELEMENTS_H_
    #define _WINDOWELEMENTS_H_

#include <SDL2/SDL.h>

struct WindowElements
{
    SDL_Window* window;
    SDL_Surface* surface;
};

#endif
