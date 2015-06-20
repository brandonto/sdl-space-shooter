/*******************************************************************//*
 * Physics component for Enemy.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-23
 * @modified    2015-02-23
 *********************************************************************/
#ifndef SPACESHOOTER_UFOPHYSICSCOMPONENT_
    #define SPACESHOOTER_UFOPHYSICSCOMPONENT_

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

class UFOPhysicsComponent : public PhysicsComponent,
                                public IObservable
{
    private:
        GameEntityFactory* gameEntityFactory;

        RenderComponent* render;
        Timer timeBasedMovementTimer;

        MovementPattern movement;

    public:
        Vector2D velocity;
        int velocityPerSecond;
        bool shooting;
        const int offScreenBuffer = 25;
        int score;

        //Constructor
        UFOPhysicsComponent(GameEntity* gameEntity,
                                WindowElements* windowElements,
                                GameEntityFactory* gameEntityFactory);

        //Destructor
        ~UFOPhysicsComponent();

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

