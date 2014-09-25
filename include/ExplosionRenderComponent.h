/*******************************************************************//*
 * Render component for Explosion.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-25
 * @modified    2014-09-25
 *********************************************************************/
#ifndef SPACESHOOTER_EXPLOSIONRENDERCOMPONENT_
    #define SPACESHOOTER_EXPLOSIONRENDERCOMPONENT_

#include "RenderComponent.h"
#include <SDL2/SDL.h>

class GameEntity;

struct WindowElements;

class ExplosionRenderComponent : public RenderComponent
{
    public:
        //Constructor
        ExplosionRenderComponent(GameEntity* gameEntity,
                                        WindowElements* windowElements,
                                        GameEntity* destroyedEntity);

        //Destructor
        ~ExplosionRenderComponent();

        //Methods
        void update();
};

#endif
