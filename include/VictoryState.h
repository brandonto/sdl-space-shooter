/*******************************************************************//*
 * This is the ApplicationState class for the victory screen. This
 * state is entered after completing all of the levels in the game
 * state.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-19
 * @modified    2015-02-19
 *********************************************************************/
#ifndef SPACESHOOTER_VICTORYSTATE_H_
    #define SPACESHOOTER_VICTORYSTATE_H_

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

class VictoryState : public ApplicationState
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
        VictoryState(ApplicationStateManager* applicationStateManager,
                  WindowElements* windowElements);

        //Destructor
        ~VictoryState();

        //GameState methods
        void onEnter();
        void onEvent();
        void onUpdate();
        void onRender();
        void onExit();
        void stateTransition(int nextState);
};

#endif

