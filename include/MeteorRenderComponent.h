/*******************************************************************//*
 * Render component for Meteor.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-14
 * @modified    2015-02-19
 *********************************************************************/
#ifndef SPACESHOOTER_METEORRENDERCOMPONENT_
    #define SPACESHOOTER_METEORRENDERCOMPONENT_

#include "RenderComponent.h"

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef linux
	#include <SDL2/SDL.h>
#endif

class GameEntity;

struct WindowElements;

class MeteorRenderComponent : public RenderComponent
{
    public:
        //Constructor
        MeteorRenderComponent(GameEntity* gameEntity,
                               WindowElements* windowElements);

        //Destructor
        ~MeteorRenderComponent();

        //Methods
        void update();
};

#endif
