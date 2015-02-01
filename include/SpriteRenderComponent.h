/*******************************************************************//*
 * Render component for misc Sprites.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-01
 * @modified    2015-02-01
 *********************************************************************/
#ifndef SPACESHOOTER_SPRITERENDERCOMPONENT_
    #define SPACESHOOTER_SPRITERENDERCOMPONENT_

#include "RenderComponent.h"
#include <string>
#include <SDL2/SDL.h>

class GameEntity;

struct WindowElements;

class SpriteRenderComponent : public RenderComponent
{
    private:
        Uint8 alpha;
        const Uint8 SELECTED_ALPHA = 255;
        Uint8 cachedAlpha;
        bool selected;

    public:
        //Constructor
        SpriteRenderComponent(GameEntity* gameEntity,
                               WindowElements* windowElements);

        //Destructor
        ~SpriteRenderComponent();

        //Methods
        void update();
        void enableBlending();
        void setAlphaBlend(Uint8 alpha);
        Uint8 getAlphaBlend();
        void setRenderRect(SDL_Rect* rect);
        void setImage(std::string path);
};

#endif
