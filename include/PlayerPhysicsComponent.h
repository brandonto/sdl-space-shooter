/*******************************************************************//*
 * Physics component for Player.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2015-02-17
 *********************************************************************/
#ifndef SPACESHOOTER_PLAYERPHYSICSCOMPONENT_
    #define SPACESHOOTER_PLAYERPHYSICSCOMPONENT_

#include "PhysicsComponent.h"
#ifdef _WIN32
	#include <SDL.h>
#endif
#ifdef linux
	#include <SDL2/SDL.h>
#endif

#include "IObserver.h"
#include "Timer.h"
#include "Vector2D.h"

class GameEntity;
class GameEntityFactory;
class RenderComponent;

struct WindowElements;

class PlayerPhysicsComponent : public PhysicsComponent,
                               public IObservable
{
    private:
        GameEntityFactory* gameEntityFactory;

        RenderComponent* render;
        Timer timeBasedMovementTimer;
        Timer projectileCapTimer;
        Timer invulnerableTimer;
        const Uint8 alphaInvulnerableLow = 0x20;
        const Uint8 alphaInvulnerableHigh = 0x80;

    public:
        Vector2D velocity;
        int velocityPerSecond;
        bool shooting;
        bool invulnerable;

        //Constructor
        PlayerPhysicsComponent(GameEntity* gameEntity, WindowElements* windowElements,
                                GameEntityFactory* gameEntityFactory);

        //Destructor
        ~PlayerPhysicsComponent();

        //Methods
        void update();
        void pauseTimers();
        void resumeTimers();
        void onHit();
        void onDestroy();

        //Virtual methods from IObservable
        //void notify(GameEntity* entity, int event);
};

enum playerEvents
{
    PLAYER_DESTROYED,
};

#endif
