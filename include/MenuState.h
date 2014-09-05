/*******************************************************************//*
 * This is the ApplicationState class for the main menu screen. This
 * state is entered after the intro state at the beginning and can be
 * navigated to from the pause state.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-09-05
 *********************************************************************/
#ifndef SPACESHOOTER_MENUSTATE_H_
    #define SPACESHOOTER_MENUSTATE_H_

#include <vector>
#include "ApplicationState.h"
#include "GameEntityManager.h"

class GameEntity;

class MenuState : public ApplicationState
{
    private:
        SDL_Event event;
        GameEntityManager gameEntityManager;
        GameEntity* background;
        std::vector<GameEntity*> mainMenu;
        SDL_Texture* blackScreen;

        bool fadeIn;
        bool fadeOut;
        Uint8 menuAlpha;
        bool blackIn;
        bool blackOut;
        Uint8 blackScreenAlpha;

        int nextState;

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
};

#endif
