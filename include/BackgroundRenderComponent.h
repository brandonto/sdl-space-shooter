/*******************************************************************//*
 * Render component for background
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-17
 * @modified    2014-09-25
 *********************************************************************/
#ifndef SPACESHOOTER_BACKGROUNDRENDERCOMPONENT_
    #define SPACESHOOTER_BACKGROUNDRENDERCOMPONENT_

#include <SDL2/SDL.h>
#include "RenderComponent.h"

class GameEntity;

struct WindowElements;

class BackgroundRenderComponent : public RenderComponent
{
    public:
        //Constructor
        BackgroundRenderComponent(GameEntity* gameEntity, WindowElements* windowElements);

        //Destructor
        ~BackgroundRenderComponent();

        //Methods
        void update();
};

#endif
