/*******************************************************************//*
 * This class encapsulates black screen fade in and fade out effects
 * from state transitions.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-05
 * @modified    2015-02-19
 *********************************************************************/
#ifndef SPACESHOOTER_BLACKSCREEN_H_
    #define SPACESHOOTER_BLACKSCREEN_H_

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef linux
	#include <SDL2/SDL.h>
#endif

#define SCREEN_OPAQUE 255
#define SCREEN_DIM 192
#define SCREEN_UNDIM 0

#define ALPHA_UPDATE 50

class Texture;
class WindowElements;

class BlackScreen
{
    private:
        Texture* blackScreen;
        WindowElements* windowElements;
        bool blackIn;
        bool blackOut;

    public:
        //Constructor
        BlackScreen(WindowElements* windowElements);

        //Destructor
        ~BlackScreen();

        //Methods
        bool isBlackingIn();
        bool isBlackingOut();
        void startBlackIn();
        void startBlackOut();
        void onUpdate();
        void onRender();
        void setAlphaBlend(Uint8 alpha);
        Uint8 getAlphaBlend();
        void screenDim();
        void screenUndim();
};

#endif
