/*******************************************************************//*
 * Several useful SDL utility functions wrapped in a namespace
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-09-03
 *********************************************************************/
#ifndef SPACESHOOTER_SDL_UTIL_H_
    #define SPACESHOOTER_SDL_UTIL_H_

#include <string>

struct SDL_Color;
struct SDL_Rect;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;
struct WindowElements;

namespace SDL_util
{
    bool initialize();
    SDL_Texture* create_texture_from_surface(WindowElements* windowElements,
                                                SDL_Surface* surface);
    SDL_Texture* create_texture_from_image(WindowElements* windowElements, std::string path);
    SDL_Surface* create_surface_from_image(std::string path);
    SDL_Texture* create_background_texture(WindowElements* windowElements, std::string path);
    SDL_Texture* create_texture_from_text(WindowElements* windowElements, std::string path,
                                            std::string text, int fontSize, SDL_Color* color);
    SDL_Surface* create_surface_from_text(std::string path, std::string text, int fontSize,
                                            SDL_Color* color);
    SDL_Texture* create_texture_from_surfaces(WindowElements* windowElements,
                                                SDL_Surface* src, SDL_Rect* srcRect,
                                                SDL_Surface* dest, SDL_Rect* destRect,
                                                bool scaled);
    void terminate();
}

#endif
