/*******************************************************************//*
 * Input component for Player.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-01
 * @modified    2015-02-19
 *********************************************************************/
#ifndef SPACESHOOTER_PLAYERINSTRUCTIONSINPUTCOMPONENT_
    #define SPACESHOOTER_PLAYERINSTRUCTIONSINPUTCOMPONENT_

#include "InputComponent.h"

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
	#include <SDL2/SDL.h>
#endif

#include "Timer.h"

class GameEntity;
class PlayerInstructionsPhysicsComponent;
class WindowElements;

class PlayerInstructionsInputComponent : public InputComponent
{
    private:
        PlayerInstructionsPhysicsComponent* physics;
        const Uint8* keyStates;

    public:
        //Constructor
        PlayerInstructionsInputComponent(GameEntity* gameEntity, WindowElements* windowElements);

        //Destructor
        ~PlayerInstructionsInputComponent();

        //Methods
        void update(SDL_Event* event);
};

#endif

