/*******************************************************************//*
 * This is the ApplicationState class for the main menu screen. This
 * state is entered after the intro state at the beginning and can be
 * navigated to from the pause state.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2015-02-20
 *********************************************************************/
#ifndef SPACESHOOTER_MENUSTATE_H_
    #define SPACESHOOTER_MENUSTATE_H_

#include <vector>
#include "ApplicationState.h"
#include "BlackScreen.h"
#include "GameEntityManager.h"
#include "Timer.h"

class GameEntity;

class MenuState : public ApplicationState
{
    private:
        SDL_Event event;
        GameEntityManager gameEntityManager;
        std::vector<GameEntity*> background;
        std::vector<GameEntity*> meteors;
        std::vector<GameEntity*> mainMenu;
        BlackScreen blackScreen;

        bool fadeIn;
        bool fadeOut;
        Uint8 menuAlpha;

        Timer meteorTimer;
        int randomMeteorTime;

        int nextState;
        int pushedState;

    public:
        //Constructor
        MenuState(ApplicationStateManager* applicationStateManager,
                  WindowElements* windowElements);

        //Destructor
        ~MenuState();

        //GameState methods
        void onEnter();
        void onEvent();
        void onUpdate();
        void onRender();
        void onExit();
        void stateTransition(int nextState);
        void statePush(int pushedState);
};

#endif
