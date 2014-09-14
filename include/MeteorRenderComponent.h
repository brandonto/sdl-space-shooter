/*******************************************************************//*
 * Render component for Meteor.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-14
 * @modified    2014-09-14
 *********************************************************************/
#ifndef SPACESHOOTER_METEORRENDERCOMPONENT_
    #define SPACESHOOTER_METEORRENDERCOMPONENT_

#include "RenderComponent.h"
#include <SDL2/SDL.h>

class GameEntity;

struct WindowElements;

class MeteorRenderComponent : public RenderComponent
{
    private:
        GameEntity* gameEntity;
        WindowElements* windowElements;

    public:
        SDL_Rect renderRect;
        SDL_Texture* sprite;
        int spriteWidth;
        int spriteHeight;
        double angle;

        //Constructor
        MeteorRenderComponent(GameEntity* gameEntity,
                               WindowElements* windowElements);

        //Destructor
        ~MeteorRenderComponent();

        //Methods
        void update();
};

#endif
