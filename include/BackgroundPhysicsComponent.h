/*******************************************************************//*
 * Physics component for background
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-13
 * @modified    2014-09-13
 *********************************************************************/
#ifndef SPACESHOOTER_BACKGROUNDPHYSICSCOMPONENT_
    #define SPACESHOOTER_BACKGROUNDPHYSICSCOMPONENT_

#include <SDL2/SDL.h>
#include "PhysicsComponent.h"

class BackgroundRenderComponent;
class GameEntity;

struct WindowElements;

class BackgroundPhysicsComponent : public PhysicsComponent
{
    private:
        GameEntity* gameEntity;
        WindowElements* windowElements;

        BackgroundRenderComponent* render;
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

