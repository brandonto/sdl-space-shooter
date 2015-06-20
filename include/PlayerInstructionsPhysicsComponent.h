/*******************************************************************//*
 * Physics component for PlayerInstructions.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-01
 * @modified    2015-02-19
 *********************************************************************/
#ifndef SPACESHOOTER_PLAYERINSTRUCTIONSPHYSICSCOMPONENTCOMPONENT_
    #define SPACESHOOTER_PLAYERINSTRUCTIONSPHYSICSCOMPONENTCOMPONENT_

#include "PhysicsComponent.h"

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
	#include <SDL2/SDL.h>
#endif

#include "Timer.h"
#include "Vector2D.h"

#define COLLISION_BUFFER 20

class GameEntity;
class GameEntityFactory;
class RenderComponent;

struct WindowElements;

class PlayerInstructionsPhysicsComponent : public PhysicsComponent
{
    private:
        GameEntityFactory* gameEntityFactory;

        RenderComponent* render;
        Timer timeBasedMovementTimer;
        Timer projectileCapTimer;

        int xGrid;
        int yGrid;
        int xMin;
        int yMin;
        int xMax;
        int yMax;

    public:
        Vector2D velocity;
        int velocityPerSecond;
        bool shooting;

        //Constructor
        PlayerInstructionsPhysicsComponent(GameEntity* gameEntity, WindowElements* windowElements,
                                GameEntityFactory* gameEntityFactory);

        //Destructor
        ~PlayerInstructionsPhysicsComponent();

        //Methods
        void update();
        void pauseTimers();
        void resumeTimers();
        void onDestroy();
};

#endif
