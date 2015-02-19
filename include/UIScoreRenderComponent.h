/*******************************************************************//*
 * Render component for UIScore
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-18
 * @modified    2015-02-18
 *********************************************************************/
#ifndef SPACESHOOTER_UISCORERENDERCOMPONENT_
    #define SPACESHOOTER_UISCORERENDERCOMPONENT_

#include "RenderComponent.h"

#include <map>

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef linux
	#include <SDL2/SDL.h>
#endif

#define SCORE_DIGITS 6

class GameEntity;

struct WindowElements;

class UIScoreRenderComponent : public RenderComponent
{
    private:
        std::map<int, Texture*> numScoreTextures;
        SDL_Rect numScoreRect[SCORE_DIGITS];

        int* scorePointer;

        //private method for power of integers
        int pow(int base, int exp);

    public:
        //Constructor
        UIScoreRenderComponent(GameEntity* gameEntity,
                               WindowElements* windowElements);

        //Destructor
        ~UIScoreRenderComponent();

        //Methods
        void update();
        void enableBlending();
        void setAlphaBlend(Uint8 alpha);
        Uint8 getAlphaBlend();
        void setScorePointer(int* ptr);
};

#endif

