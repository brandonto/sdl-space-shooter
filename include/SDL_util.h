/*******************************************************************//*
 * Several useful SDL utility functions wrapped in a namespace
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-08-20
 *********************************************************************/
#ifndef SPACESHOOTER_SDL_UTIL_H_
    #define SPACESHOOTER_SDL_UTIL_H_

#include <string>

struct SDL_Texture;
struct SDL_Renderer;

namespace SDL_util
{
    bool initialize();
    SDL_Texture* load_image(SDL_Renderer* renderer, std::string path);
}

#endif
