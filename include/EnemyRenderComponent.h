/*******************************************************************//*
 * Render component for Enemy.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-17
 * @modified    2014-09-17
 *********************************************************************/
#ifndef SPACESHOOTER_ENEMYRENDERCOMPONENT_
    #define SPACESHOOTER_ENEMYRENDERCOMPONENT_

#include "RenderComponent.h"
#include <SDL2/SDL.h>

class GameEntity;

struct WindowElements;

class EnemyRenderComponent : public RenderComponent
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
        EnemyRenderComponent(GameEntity* gameEntity,
                               WindowElements* windowElements);

        //Destructor
        ~EnemyRenderComponent();

        //Methods
        void update();
};

#endif
