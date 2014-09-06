/*******************************************************************//*
 * Implementation of the BlackScreen class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-05
 * @modified    2014-09-06
 *********************************************************************/
#include "BlackScreen.h"

#include "SDL_util.h"
#include "WindowElements.h"

BlackScreen::BlackScreen(WindowElements* windowElements)
:   windowElements(windowElements), alpha(255), blackIn(false), blackOut(false)
{
    Uint32 rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif

    SDL_Surface* blackScreenSurface = SDL_CreateRGBSurface(0, windowElements->WINDOW_WIDTH,
                                                        windowElements->WINDOW_HEIGHT, 32,
                                                        rmask, gmask, bmask, amask);

    SDL_FillRect(blackScreenSurface, NULL,
                 SDL_MapRGB(blackScreenSurface->format, 0x00, 0x00, 0x00));

    blackScreen = SDL_util::create_texture_from_surface(windowElements, blackScreenSurface);

    SDL_FreeSurface(blackScreenSurface);

    SDL_SetTextureBlendMode(blackScreen, SDL_BLENDMODE_BLEND);
}

BlackScreen::~BlackScreen()
{
    SDL_DestroyTexture(blackScreen);
    blackScreen = NULL;
}

bool BlackScreen::isBlackingIn()
{
    return blackIn;
}

bool BlackScreen::isBlackingOut()
{
    return blackOut;
}

void BlackScreen::startBlackIn()
{
    if (!blackOut) { blackIn = true; }
}

void BlackScreen::startBlackOut()
{
    if (!blackIn) { blackOut = true; }
}

void BlackScreen::onUpdate()
{
    if (blackIn)
    {
        if (alpha>0)
        {
            if ( alpha == 5 ) { alpha = 0; }
            else { alpha-=50; }
            if ( alpha == 0 ) { blackIn = false; }
            SDL_SetTextureAlphaMod(blackScreen, alpha);
        }
    }
    else if (blackOut)
    {
        if (alpha<255)
        {
            if ( alpha == 250 ) { alpha = 255; }
            else { alpha+=50; }
            if ( alpha == 255 ) { blackOut = false; }
            SDL_SetTextureAlphaMod(blackScreen, alpha);
        }
    }
}

void BlackScreen::onRender()
{
    SDL_RenderCopy(windowElements->renderer, blackScreen, NULL, NULL);
}
