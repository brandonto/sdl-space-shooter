/*******************************************************************//*
 * Input component for Player.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2014-09-19
 *********************************************************************/
#ifndef SPACESHOOTER_PLAYERINPUTCOMPONENT_
    #define SPACESHOOTER_PLAYERINPUTCOMPONENT_

#include "InputComponent.h"
#include <SDL2/SDL.h>
#include "Timer.h"

class GameEntity;
class PlayerPhysicsComponent;
class WindowElements;

class PlayerInputComponent : public InputComponent
{
    private:
        PlayerPhysicsComponent* physics;
        const Uint8* keyStates;

    public:
        //Constructor
        PlayerInputComponent(GameEntity* gameEntity, WindowElements* windowElements);

        //Destructor
        ~PlayerInputComponent();

        //Methods
        void update(SDL_Event* event);
};

#endif
