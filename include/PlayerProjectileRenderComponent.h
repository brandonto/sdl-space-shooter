/*******************************************************************//*
 * Render component for PlayerProjectile.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-08
 * @modified    2014-09-25
 *********************************************************************/
#ifndef SPACESHOOTER_PLAYERPROJECTILERENDERCOMPONENT_
    #define SPACESHOOTER_PLAYERPROJECTILERENDERCOMPONENT_

#include "RenderComponent.h"
#ifdef _WIN32
	#include <SDL.h>
#endif
#ifdef linux
	#include <SDL2/SDL.h>
#endif


class GameEntity;

struct WindowElements;

class PlayerProjectileRenderComponent : public RenderComponent
{
    public:
        //Constructor
        PlayerProjectileRenderComponent(GameEntity* gameEntity,
                                        WindowElements* windowElements,
                                        GameEntity* playerEntity);

        //Destructor
        ~PlayerProjectileRenderComponent();

        //Methods
        void update();
};

#endif
