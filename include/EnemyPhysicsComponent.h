/*******************************************************************//*
 * Physics component for Enemy.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-17
 * @modified    2015-02-21
 *********************************************************************/
#ifndef SPACESHOOTER_ENEMYPHYSICSCOMPONENT_
    #define SPACESHOOTER_ENEMYPHYSICSCOMPONENT_

#include "PhysicsComponent.h"

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef linux
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

class EnemyPhysicsComponent : public PhysicsComponent,
                                public IObservable
{
    private:
        GameEntityFactory* gameEntityFactory;

        RenderComponent* render;
        Timer timeBasedMovementTimer;
        Timer projectileCapTimer;

        MovementPattern movement;

    public:
        Vector2D velocity;
        int velocityPerSecond;
        bool shooting;
        const int offScreenBuffer = 25;
        int score;

        //Constructor
        EnemyPhysicsComponent(GameEntity* gameEntity,
                                WindowElements* windowElements,
                                GameEntityFactory* gameEntityFactory);

        //Destructor
        ~EnemyPhysicsComponent();

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
