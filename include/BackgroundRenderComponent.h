/*******************************************************************//*
 * Render component for background
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-17
 * @modified    2014-08-27
 *********************************************************************/
#ifndef SPACESHOOTER_BACKGROUNDRENDERCOMPONENT_
    #define SPACESHOOTER_BACKGROUNDRENDERCOMPONENT_

#include "RenderComponent.h"

struct SDL_Texture;
struct WindowElements;

class BackgroundRenderComponent : public RenderComponent
{
    private:
        SDL_Texture* sprite;
        WindowElements* windowElements;
        int offset;

    public:
        //Constructor
        BackgroundRenderComponent(WindowElements* windowElements);

        //Destructor
        ~BackgroundRenderComponent();

        //Methods
        void update(GameEntity* gameEntity);
};

#endif
