/*******************************************************************//*
 * Implementation of SDL_util class
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-08-20
 *********************************************************************/
#include "SDL_util.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace SDL_util
{
    bool initialize()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            return false;
        }

        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
            return false;
        }

        return true;
    }

    SDL_Texture* load_image(SDL_Renderer* renderer, std::string path)
    {
        SDL_Texture* texture = NULL;
        SDL_Surface* surface = IMG_Load(path.c_str());
        if (surface==NULL)
        {
            printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        }
        else
        {
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            if(texture==NULL)
            {
                printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
            }

            SDL_FreeSurface(surface);
        }

        return texture;
    }

    //SDL_Renderer* create
}
