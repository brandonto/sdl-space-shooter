/*******************************************************************//*
 * This is the ApplicationState class for the game menu screen. This
 * state is entered after pressing ESC in the game state.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-02
 * @modified    2015-02-11
 *********************************************************************/
#ifndef SPACESHOOTER_GAMEMENUSTATE_H_
    #define SPACESHOOTER_GAMEMENUSTATE_H_

#ifdef _WIN32
	#include <SDL.h>
#endif
#ifdef linux
	#include <SDL2/SDL.h>
#endif

#include "ApplicationState.h"
#include "BlackScreen.h"
#include "GameEntityManager.h"

class GameEntity;

class GameMenuState : public ApplicationState
{
    private:
        SDL_Event event;

        GameEntityManager gameEntityManager;
        std::vector<GameEntity*> uiEntities;
        BlackScreen blackScreen;

        bool fadeIn;
        bool fadeOut;
        Uint8 menuAlpha;
        bool transitioningStates;

        int nextState;

    public:
        //Constructor
        GameMenuState(ApplicationStateManager* applicationStateManager,
                  WindowElements* windowElements);

        //Destructor
        ~GameMenuState();

        //GameState methods
        void onEnter();
        void onEvent();
        void onUpdate();
        void onRender();
        void onExit();
        void stateTransition(int nextState);
};

#endif
