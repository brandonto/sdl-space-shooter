/*******************************************************************//*
 * This is the ApplicationState class for the game menu screen. This
 * state is entered after pressing ESC in the game state.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-02
 * @modified    2015-02-20
 *********************************************************************/
#ifndef SPACESHOOTER_GAMEMENUSTATE_H_
    #define SPACESHOOTER_GAMEMENUSTATE_H_

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
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

        int nextState;
        int pushedState;

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
        void statePush(int pushedState);
        void statePop();
};

#endif
