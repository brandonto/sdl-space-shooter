/*******************************************************************//*
 * Structure of useful SDL window variables. 
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-06
 * @modified    2014-08-20
 *********************************************************************/
#ifndef SPACESHOOTER_WINDOWELEMENTS_H_
    #define SPACESHOOTER_WINDOWELEMENTS_H_

struct SDL_Window;
struct SDL_Surface;
struct SDL_Renderer;

struct WindowElements
{
    SDL_Window* window;
    SDL_Surface* surface;
    SDL_Renderer* renderer;
};

#endif
