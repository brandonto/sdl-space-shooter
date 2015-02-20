/*******************************************************************//*
 * This is the ApplicationState class for the options screen. This
 * state is entered if the player clicks on the options button in
 * the menu state
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-20
 * @modified    2015-02-20
 *********************************************************************/
#ifndef SPACESHOOTER_OPTIONSSTATE_H_
    #define SPACESHOOTER_OPTIONSSTATE_H_

#include <vector>
#include "ApplicationState.h"
#include "GameEntityManager.h"

class GameEntity;

class OptionsState : public ApplicationState
{
    private:
        SDL_Event event;
        GameEntityManager gameEntityManager;
        std::vector<GameEntity*> uiEntities;
        GameEntity* bgmCheck;

        bool fadeIn;
        bool fadeOut;
        Uint8 uiAlpha;

        int nextState;

    public:
        //Constructor
        OptionsState(ApplicationStateManager* applicationStateManager,
                  WindowElements* windowElements);

        //Destructor
        ~OptionsState();

        //GameState methods
        void onEnter();
        void onEvent();
        void onUpdate();
        void onRender();
        void onExit();
        void stateTransition(int nextState);
        void statePop();
};

#endif

