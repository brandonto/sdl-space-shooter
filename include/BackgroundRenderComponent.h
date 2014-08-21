/*******************************************************************//*
 * Render component for background
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-17
 * @modified    2014-08-20
 *********************************************************************/
#ifndef SPACESHOOTER_BACKGROUNDRENDERCOMPONENT_
    #define SPACESHOOTER_BACKGROUNDRENDERCOMPONENT_

#include "RenderComponent.h"

struct SDL_Texture;
struct SDL_Renderer;

class BackgroundRenderComponent : public RenderComponent
{
    private:
        SDL_Texture* sprite;
        SDL_Renderer* renderer;

    public:
        //Constructor
        BackgroundRenderComponent(SDL_Renderer* renderer);

        //Destructor
        ~BackgroundRenderComponent();

        //Methods
        void update(GameEntity* gameEntity);
};

#endif
