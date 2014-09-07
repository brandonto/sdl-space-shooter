/*******************************************************************//*
 * Render component for Player.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2014-09-06
 *********************************************************************/
#ifndef SPACESHOOTER_PLAYERRENDERCOMPONENT_
    #define SPACESHOOTER_PLAYERRENDERCOMPONENT_

#include "RenderComponent.h"
#include <SDL2/SDL.h>

class GameEntity;

struct WindowElements;

class PlayerRenderComponent : public RenderComponent
{
    private:
        GameEntity* gameEntity;
        WindowElements* windowElements;

    public:
        SDL_Rect renderRect;
        SDL_Texture* sprite;
        int spriteWidth;
        int spriteHeight;

        //Constructor
        PlayerRenderComponent(GameEntity* gameEntity,
                               WindowElements* windowElements);

        //Destructor
        ~PlayerRenderComponent();

        //Methods
        void update();
};

#endif
