/*******************************************************************//*
 * Physics component for Boss.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-21
 * @modified    2015-02-23
 *********************************************************************/
#ifndef SPACESHOOTER_BOSSPHYSICSCOMPONENT_
    #define SPACESHOOTER_BOSSPHYSICSCOMPONENT_

#include "PhysicsComponent.h"

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
	#include <SDL2/SDL.h>
#endif

#include "IObserver.h"
#include "MovementPattern.h"
#include "Timer.h"
#include "Vector2D.h"

class GameEntity;
class GameEntityFactory;
class RenderComponent;

struct WindowElements;

class BossPhysicsComponent : public PhysicsComponent,
                                public IObservable
{
    private:
        GameEntityFactory* gameEntityFactory;

        RenderComponent* render;
        Timer timeBasedMovementTimer;
        Timer projectileCapTimer;
        Timer sprayTimer;
        Timer sprayCapTimer;
        Timer spawnUFOTimer;
        Timer nukeTimer;

        MovementPattern movement;

    public:
        bool shooting;
        const int offScreenBuffer = 25;

        //Constructor
        BossPhysicsComponent(GameEntity* gameEntity,
                                WindowElements* windowElements,
                                GameEntityFactory* gameEntityFactory);

        //Destructor
        ~BossPhysicsComponent();

        //Methods
        void update();
        void pauseTimers();
        void resumeTimers();
        void onHit();
        void onDestroy();
        MovementPattern* getMovementPattern();

        //Virtual methods from IObservable
        //void notify(GameEntity* entity, int event);
};

#endif

