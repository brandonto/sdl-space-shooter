/*******************************************************************//*
 * Several useful SDL utility functions wrapped in a namespace
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-08-27
 *********************************************************************/
#ifndef SPACESHOOTER_SDL_UTIL_H_
    #define SPACESHOOTER_SDL_UTIL_H_

#include <string>

struct SDL_Texture;
struct SDL_Renderer;
struct WindowElements;

namespace SDL_util
{
    bool initialize();
    SDL_Texture* load_image(WindowElements* windowElements, std::string path);
    SDL_Texture* load_background(WindowElements* windowElements, std::string path);
}

#endif
