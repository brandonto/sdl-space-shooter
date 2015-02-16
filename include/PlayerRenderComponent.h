/*******************************************************************//*
 * Render component for Player.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2015-02-16
 *********************************************************************/
#ifndef SPACESHOOTER_PLAYERRENDERCOMPONENT_
    #define SPACESHOOTER_PLAYERRENDERCOMPONENT_

#include "RenderComponent.h"

#include <SDL2/SDL.h>
#include <map>

class GameEntity;

struct WindowElements;

class PlayerRenderComponent : public RenderComponent
{
    private:
        std::map<int, Texture*> damagedSprites;

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
        void addDamagedSprite(int health, Texture* texture);
};

#endif
