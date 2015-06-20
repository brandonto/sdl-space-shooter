/*******************************************************************//*
 * Physics component for background
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-13
 * @modified    2015-02-19
 *********************************************************************/
#ifndef SPACESHOOTER_BACKGROUNDPHYSICSCOMPONENT_
    #define SPACESHOOTER_BACKGROUNDPHYSICSCOMPONENT_

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
	#include <SDL2/SDL.h>
#endif

#include "PhysicsComponent.h"

class RenderComponent;
class GameEntity;

struct WindowElements;

class BackgroundPhysicsComponent : public PhysicsComponent
{
    private:
        RenderComponent* render;
        int offsetIncrementCounter;
        int offsetIncrementModulus;

    public:
        //Constructor
        BackgroundPhysicsComponent(GameEntity* gameEntity, WindowElements* windowElements);

        //Destructor
        ~BackgroundPhysicsComponent();

        //Methods
        void update();
};

#endif

