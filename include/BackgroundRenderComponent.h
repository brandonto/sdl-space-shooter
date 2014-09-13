/*******************************************************************//*
 * Render component for background
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-17
 * @modified    2014-09-13
 *********************************************************************/
#ifndef SPACESHOOTER_BACKGROUNDRENDERCOMPONENT_
    #define SPACESHOOTER_BACKGROUNDRENDERCOMPONENT_

#include <SDL2/SDL.h>
#include "RenderComponent.h"

class GameEntity;

struct WindowElements;

class BackgroundRenderComponent : public RenderComponent
{
    private:
        GameEntity* gameEntity;
        WindowElements* windowElements;

    public:
        SDL_Rect renderRect;
        SDL_Texture* sprite;

        //Constructor
        BackgroundRenderComponent(GameEntity* gameEntity, WindowElements* windowElements);

        //Destructor
        ~BackgroundRenderComponent();

        //Methods
        void update();
};

#endif
