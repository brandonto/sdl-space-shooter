/*******************************************************************//*
 * This class encapsulates black screen fade in and fade out effects
 * from state transitions.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-05
 * @modified    2015-02-02
 *********************************************************************/
#ifndef SPACESHOOTER_BLACKSCREEN_H_
    #define SPACESHOOTER_BLACKSCREEN_H_

#include <SDL2/SDL.h>

class WindowElements;

class BlackScreen
{
    private:
        SDL_Texture* blackScreen;
        WindowElements* windowElements;
        Uint8 alpha;
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
        void setAlpha(Uint8 alpha);

};

#endif
