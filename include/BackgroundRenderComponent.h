/*******************************************************************//*
 * Render component for background
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-17
 * @modified    2015-02-19
 *********************************************************************/
#ifndef SPACESHOOTER_BACKGROUNDRENDERCOMPONENT_
    #define SPACESHOOTER_BACKGROUNDRENDERCOMPONENT_

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef linux
	#include <SDL2/SDL.h>
#endif

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
