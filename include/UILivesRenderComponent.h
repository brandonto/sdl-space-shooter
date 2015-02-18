/*******************************************************************//*
 * Render component for UILives
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-17
 * @modified    2015-02-18
 *********************************************************************/
#ifndef SPACESHOOTER_UILIVESRENDERCOMPONENT_
    #define SPACESHOOTER_UILIVESRENDERCOMPONENT_

#include "RenderComponent.h"

#ifdef _WIN32
	#include <SDL.h>
#endif
#ifdef linux
	#include <SDL2/SDL.h>
#endif

#include <map>

class GameEntity;

struct WindowElements;

class UILivesRenderComponent : public RenderComponent
{
    private:
        Texture* xTexture;
        SDL_Rect xRect;
        std::map<int, Texture*> numLivesTextures;
        SDL_Rect numLivesRect;

        int* livesPointer;

    public:
        //Constructor
        UILivesRenderComponent(GameEntity* gameEntity,
                               WindowElements* windowElements);

        //Destructor
        ~UILivesRenderComponent();

        //Methods
        void update();
        void enableBlending();
        void setAlphaBlend(Uint8 alpha);
        Uint8 getAlphaBlend();
        void setLivesPointer(int* ptr);
};

#endif

