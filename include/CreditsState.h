/*******************************************************************//*
 * This is the ApplicationState class for the credits screen. This
 * state is entered if the player clicks on the Credits button in
 * the menu state
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-01
 * @modified    2015-02-01
 *********************************************************************/
#ifndef SPACESHOOTER_CREDITSSTATE_H_
    #define SPACESHOOTER_CREDITSSTATE_H_

#include <vector>
#include "ApplicationState.h"
#include "BlackScreen.h"
#include "GameEntityManager.h"

class GameEntity;

class CreditsState : public ApplicationState
{
    private:
        SDL_Event event;
        GameEntityManager gameEntityManager;
        GameEntity* background;
        std::vector<GameEntity*> uiCredits;
        BlackScreen blackScreen;

        bool fadeIn;
        bool fadeOut;
        Uint8 uiAlpha;

        int nextState;

    public:
        //Constructor
        CreditsState(ApplicationStateManager* applicationStateManager,
                  WindowElements* windowElements);

        //Destructor
        ~CreditsState();

        //GameState methods
        void onEnter();
        void onEvent();
        void onUpdate();
        void onRender();
        void onExit();
        void stateTransition(int nextState);
};

#endif
