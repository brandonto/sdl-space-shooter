/*******************************************************************//*
 * Implementation of the BlackScreen class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-05
 * @modified    2015-02-06
 *********************************************************************/
#include "BlackScreen.h"

#include "SDL_util.h"
#include "Texture.h"
#include "WindowElements.h"

BlackScreen::BlackScreen(WindowElements* windowElements)
:   windowElements(windowElements),
    blackIn(false),
    blackOut(false)
{
    Uint32 rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xFF000000;
        gmask = 0x00FF0000;
        bmask = 0x0000FF00;
        amask = 0x000000FF;
    #else
        rmask = 0x000000FF;
        gmask = 0x0000FF00;
        bmask = 0x00FF0000;
        amask = 0xFF000000;
    #endif

    SDL_Surface* blackScreenSurface = SDL_CreateRGBSurface(
                                            0,
                                            windowElements->WINDOW_WIDTH,
                                            windowElements->WINDOW_HEIGHT,
                                            32,
                                            rmask,
                                            gmask,
                                            bmask,
                                            amask);

    SDL_FillRect(
        blackScreenSurface,
        NULL,
        SDL_MapRGB(blackScreenSurface->format, 0x00, 0x00, 0x00));

    SDL_Texture* sprite = SDL_util::create_texture_from_surface(windowElements, blackScreenSurface);

    blackScreen = new Texture(windowElements);
    blackScreen->setTexture(sprite);
    blackScreen->enableAlphaBlend();
    sprite = NULL;

    SDL_FreeSurface(blackScreenSurface);
    blackScreenSurface = NULL;

}

BlackScreen::~BlackScreen()
{
    delete blackScreen;
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
    int alpha = blackScreen->getAlphaBlend();

    if (blackIn)
    {
        if (alpha>0)
        {
            if ( alpha == 5 ) { alpha = 0; }
            else { alpha -= ALPHA_UPDATE; }
            if ( alpha == 0 ) { blackIn = false; }
            blackScreen->setAlphaBlend(alpha);
        }
    }
    else if (blackOut)
    {
        if (alpha<255)
        {
            if ( alpha == 250 ) { alpha = 255; }
            else { alpha += ALPHA_UPDATE; }
            if ( alpha == SCREEN_OPAQUE ) { blackOut = false; }
            blackScreen->setAlphaBlend(alpha);
        }
    }
}

void BlackScreen::onRender()
{
    if (blackScreen->getTexture() != NULL)
    {
        SDL_RenderCopy(windowElements->renderer, blackScreen->getTexture(), NULL, NULL);
    }
}

void BlackScreen::setAlphaBlend(Uint8 alpha)
{
    blackScreen->setAlphaBlend(alpha);
}

Uint8 BlackScreen::getAlphaBlend()
{
    return blackScreen->getAlphaBlend();
}

void BlackScreen::screenDim()
{
    blackScreen->setAlphaBlend(SCREEN_DIM);
}

void BlackScreen::screenUndim()
{
    blackScreen->setAlphaBlend(SCREEN_UNDIM);
}
