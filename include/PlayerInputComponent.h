/*******************************************************************//*
 * Input component for Player.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2014-09-08
 *********************************************************************/
#ifndef SPACESHOOTER_PLAYERINPUTCOMPONENT_
    #define SPACESHOOTER_PLAYERINPUTCOMPONENT_

#include "InputComponent.h"
#include <SDL2/SDL.h>

class GameEntity;
class GameEntityManager;
class PlayerPhysicsComponent;
class WindowElements;

class PlayerInputComponent : public InputComponent
{
    private:
        GameEntity* gameEntity;
        WindowElements* windowElements;
        GameEntityManager* gameEntityManager;

        PlayerPhysicsComponent* physics;

    public:
        //Constructor
        PlayerInputComponent(GameEntity* gameEntity, WindowElements* windowElements,
                            GameEntityManager* gameEntityManager);

        //Destructor
        ~PlayerInputComponent();

        //Methods
        void update(SDL_Event* event);
};

#endif
