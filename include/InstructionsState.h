/*******************************************************************//*
 * This is the ApplicationState class for the instructions screen. This
 * state is entered if the player clicks on the instructions button in
 * the menu state
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-01-31
 * @modified    2015-02-10
 *********************************************************************/
#ifndef SPACESHOOTER_INSTRUCTIONSSTATE_H_
    #define SPACESHOOTER_INSTRUCTIONSSTATE_H_

#include <vector>
#include "ApplicationState.h"
#include "BlackScreen.h"
#include "GameEntityManager.h"

class GameEntity;

class InstructionsState : public ApplicationState
{
    private:
        SDL_Event event;
        GameEntityManager gameEntityManager;
        std::vector<GameEntity*> backgroundEntities;
        std::vector<GameEntity*> uiEntities;
        std::vector<GameEntity*> physicalEntities;
        BlackScreen blackScreen;

        bool fadeIn;
        bool fadeOut;
        Uint8 uiAlpha;

        int nextState;

    public:
        //Constructor
        InstructionsState(ApplicationStateManager* applicationStateManager,
                  WindowElements* windowElements);

        //Destructor
        ~InstructionsState();

        //GameState methods
        void onEnter();
        void onEvent();
        void onUpdate();
        void onRender();
        void onExit();
        void stateTransition(int nextState);
};

#endif
