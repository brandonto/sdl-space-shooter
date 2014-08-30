/*******************************************************************//*
 * Render component for UI title
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-28
 * @modified    2014-08-30
 *********************************************************************/
#ifndef SPACESHOOTER_UITITLERENDERCOMPONENT_
    #define SPACESHOOTER_UITITLERENDERCOMPONENT_

#include "RenderComponent.h"
#include <SDL2/SDL.h>

class GameEntity;

struct SDL_Texture;
struct WindowElements;

class UITitleRenderComponent : public RenderComponent
{
    private:
        SDL_Rect renderRect;
        SDL_Texture* sprite;
        WindowElements* windowElements;

    public:
        //Constructor
        UITitleRenderComponent(GameEntity* gameEntity,
                               WindowElements* windowElements);

        //Destructor
        ~UITitleRenderComponent();

        //Methods
        void update(GameEntity* gameEntity);
};

#endif
