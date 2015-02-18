/*******************************************************************//*
 * Render component for Explosion.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-25
 * @modified    2015-02-06
 *********************************************************************/
#ifndef SPACESHOOTER_EXPLOSIONRENDERCOMPONENT_
    #define SPACESHOOTER_EXPLOSIONRENDERCOMPONENT_

#include "RenderComponent.h"
#ifdef _WIN32
	#include <SDL.h>
#endif
#ifdef linux
	#include <SDL2/SDL.h>
#endif


class GameEntity;

struct WindowElements;

class ExplosionRenderComponent : public RenderComponent
{
    private:

    public:
        //Constructor
        ExplosionRenderComponent(GameEntity* gameEntity,
                                        WindowElements* windowElements,
                                        GameEntity* destroyedEntity);

        //Destructor
        ~ExplosionRenderComponent();

        //Methods
        void update();
        bool advanceAnimation();
};

#endif
