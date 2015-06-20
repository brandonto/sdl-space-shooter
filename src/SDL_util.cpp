/*******************************************************************//*
 * Implementation of SDL_util class
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2015-02-18
 *********************************************************************/
#include "SDL_util.h"

#include <cstdio>
#include <cstddef>

#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
	#include <SDL_ttf.h>
	#include <SDL_mixer.h>
#endif

#ifdef __linux
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_ttf.h>
	#include <SDL2/SDL_mixer.h>
#endif

#include "WindowElements.h"

namespace SDL_util
{
    bool initialize()
    {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
            return false;
        }

        // Initialize SDL_image
        int imgFlags = IMG_INIT_PNG;
        if(!(IMG_Init(imgFlags) & imgFlags))
        {
            printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            return false;
        }

        // Initialize SDL_tff
        if(TTF_Init() == -1)
        {
            printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            return false;
        }

        // Initialize SDL_mixer
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            return false;
        }

        return true;
    }

    SDL_Texture* create_texture_from_surface(WindowElements* windowElements, SDL_Surface* surface)
    {
        SDL_Texture* texture = NULL;

        texture = SDL_CreateTextureFromSurface(windowElements->renderer, surface);
        if(texture==NULL)
        {
            printf("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
        }

        return texture;
    }

    SDL_Texture* create_texture_from_image(WindowElements* windowElements, std::string path)
    {
        SDL_Surface* surface = NULL;
        SDL_Texture* texture = NULL;

        surface = IMG_Load(path.c_str());
        if (surface==NULL)
        {
            printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        }
        else
        {
            texture = SDL_CreateTextureFromSurface(windowElements->renderer, surface);
            if(texture==NULL)
            {
                printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            }

            SDL_FreeSurface(surface);
        }

        return texture;
    }

    SDL_Surface* create_surface_from_image(std::string path)
    {
        SDL_Surface* surface = NULL;

        surface = IMG_Load(path.c_str());
        if (surface==NULL)
        {
            printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        }

        return surface;
    }

    SDL_Texture* create_background_texture(WindowElements* windowElements, std::string path)
    {
        SDL_Surface* backgroundSurface = NULL;
        SDL_Surface* surface = NULL;
        SDL_Texture* texture = NULL;
        int fitWidth, fitHeight;
        SDL_Rect temp;

        backgroundSurface = SDL_CreateRGBSurface(0, windowElements->WINDOW_WIDTH, windowElements->WINDOW_HEIGHT, 32, 0, 0, 0, 0);
        if (backgroundSurface==NULL)
        {
            printf("Unable to create SDL_Surface! SDL Error: %s\n", SDL_GetError());
            return texture;
        }

        surface = IMG_Load(path.c_str());
        if (surface==NULL)
        {
            printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
            return texture;
        }

        fitWidth = windowElements->WINDOW_HEIGHT / surface->w;
        fitHeight = windowElements->WINDOW_HEIGHT / surface->h;
        temp.w = surface->w;
        temp.h = surface->h;
        for (int i=0; i<=fitWidth; i++)
        {
            for (int j=0; j<=fitHeight; j++)
            {
                temp.x = i * surface->w;
                temp.y = j * surface->h;
                SDL_BlitSurface(surface, NULL, backgroundSurface, &(temp));
            }
        }

        texture = SDL_CreateTextureFromSurface(windowElements->renderer, backgroundSurface);
        if(texture==NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        SDL_FreeSurface(backgroundSurface);
        SDL_FreeSurface(surface);

        return texture;
    }

    SDL_Texture* create_texture_from_text(WindowElements* windowElements, std::string path,
                                        std::string text, int fontSize, SDL_Color* color)
    {
        TTF_Font* font = NULL;
        SDL_Surface* textSurface = NULL;
        SDL_Texture* texture = NULL;

        font = TTF_OpenFont(path.c_str(), fontSize);
        if (font==NULL)
        {
            printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
            return texture;
        }

        textSurface = TTF_RenderText_Solid(font, text.c_str(), *color);
        if (textSurface==NULL)
        {
            printf("Unable to create surface from text! SDL_ttf Error: %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return texture;
        }

        texture = SDL_CreateTextureFromSurface(windowElements->renderer, textSurface);
        if (texture==NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }

        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);

        return texture;
    }

    SDL_Surface* create_surface_from_text(std::string path, std::string text, int fontSize,
                                            SDL_Color* color)
    {
        TTF_Font* font = NULL;
        SDL_Surface* textSurface = NULL;

        font = TTF_OpenFont(path.c_str(), fontSize);
        if (font==NULL)
        {
            printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
            return textSurface;
        }

        textSurface = TTF_RenderText_Solid(font, text.c_str(), *color);
        if (textSurface==NULL)
        {
            printf("Unable to create surface from text! SDL_ttf Error: %s\n", TTF_GetError());
        }

        TTF_CloseFont(font);

        return textSurface;
    }

    SDL_Texture* create_texture_from_surfaces(WindowElements* windowElements,
                                                SDL_Surface* src, SDL_Rect* srcRect,
                                                SDL_Surface* dest, SDL_Rect* destRect,
                                                bool scaled)
    {
        SDL_Texture* texture = NULL;

        //Due to a bug in SDL2, SDL_Surface* src must be converted to same pixel format as 
        //SDL_Surface* dest in order to do scaled blitting
        //
        //More info: http://forums.libsdl.org/viewtopic.php?t=9975&highlight=sdlblitscaled
        SDL_Surface* convertedsrc = NULL;
        convertedsrc = SDL_ConvertSurface(src, dest->format, 0);
        if (convertedsrc==NULL)
        {
            printf("Unable to convert src pixel format to match dest! SDL_Error: %s\n", SDL_GetError());
            return texture;
        }

        if (scaled)
        {
            SDL_BlitScaled(convertedsrc, srcRect, dest, destRect);
        }
        else
        {
            SDL_BlitSurface(convertedsrc, srcRect, dest, destRect);
        }

        texture = SDL_CreateTextureFromSurface(windowElements->renderer, dest);
        if(texture==NULL)
        {
            printf("Unable to create texture from surfaces! SDL Error: %s\n", SDL_GetError());
        }

        SDL_FreeSurface(convertedsrc);

        return texture;
    }

    //SDL_Renderer* create

    void terminate()
    {
        Mix_Quit();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }
}
