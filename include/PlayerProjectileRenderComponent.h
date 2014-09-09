/*******************************************************************//*
 * Render component for PlayerProjectile.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-08
 * @modified    2014-09-08
 *********************************************************************/
#ifndef SPACESHOOTER_PLAYERPROJECTILERENDERCOMPONENT_
    #define SPACESHOOTER_PLAYERPROJECTILERENDERCOMPONENT_

#include "RenderComponent.h"
#include <SDL2/SDL.h>

class GameEntity;

struct WindowElements;

class PlayerProjectileRenderComponent : public RenderComponent
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
        PlayerProjectileRenderComponent(GameEntity* gameEntity,
                                        WindowElements* windowElements,
                                        GameEntity* playerEntity);

        //Destructor
        ~PlayerProjectileRenderComponent();

        //Methods
        void update();
};

#endif
