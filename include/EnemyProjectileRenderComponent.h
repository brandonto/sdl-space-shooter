/*******************************************************************//*
 * Render component for EnemyProjectile.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-17
 * @modified    2015-02-21
 *********************************************************************/
#ifndef SPACESHOOTER_ENEMYPROJECTILERENDERCOMPONENT_
    #define SPACESHOOTER_ENEMYPROJECTILERENDERCOMPONENT_

#include "RenderComponent.h"

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef linux
	#include <SDL2/SDL.h>
#endif

class GameEntity;

struct WindowElements;

class EnemyProjectileRenderComponent : public RenderComponent
{
    public:
        //Constructor
        EnemyProjectileRenderComponent(GameEntity* gameEntity,
                                        WindowElements* windowElements);

        //Destructor
        ~EnemyProjectileRenderComponent();

        //Methods
        void update();
};

#endif
