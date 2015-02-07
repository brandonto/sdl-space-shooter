/*******************************************************************//*
 * Render component for Player.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2015-02-06
 *********************************************************************/
#ifndef SPACESHOOTER_PLAYERRENDERCOMPONENT_
    #define SPACESHOOTER_PLAYERRENDERCOMPONENT_

#include "RenderComponent.h"
#include <SDL2/SDL.h>

class GameEntity;

struct WindowElements;

class PlayerRenderComponent : public RenderComponent
{
    public:
        //Constructor
        PlayerRenderComponent(GameEntity* gameEntity,
                               WindowElements* windowElements);

        //Destructor
        ~PlayerRenderComponent();

        //Methods
        void update();
        void enableBlending();
        void setAlphaBlend(Uint8 alpha);
        Uint8 getAlphaBlend();
};

#endif
