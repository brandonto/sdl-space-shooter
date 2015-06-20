/*******************************************************************//*
 * Render component for Enemy.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-17
 * @modified    2015-02-19
 *********************************************************************/
#ifndef SPACESHOOTER_ENEMYRENDERCOMPONENT_
    #define SPACESHOOTER_ENEMYRENDERCOMPONENT_

#include "RenderComponent.h"

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
	#include <SDL2/SDL.h>
#endif

class GameEntity;

struct WindowElements;

class EnemyRenderComponent : public RenderComponent
{
    public:
        //Constructor
        EnemyRenderComponent(GameEntity* gameEntity,
                               WindowElements* windowElements);

        //Destructor
        ~EnemyRenderComponent();

        //Methods
        void update();
};

#endif
