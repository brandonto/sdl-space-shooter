/*******************************************************************//*
 * Render component for misc Sprites.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-01
 * @modified    2015-02-06
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

    public:
        //Constructor
        SpriteRenderComponent(GameEntity* gameEntity,
                               WindowElements* windowElements);

        //Destructor
        ~SpriteRenderComponent();

        //Methods
        void update();
        void setRenderRect(SDL_Rect* rect);
};

#endif
