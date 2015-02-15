/*******************************************************************//*
 * This is the ApplicationState class for the game. This state is
 * entered after clicking the "Play" button from the menu state
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-05
 * @modified    2015-02-15
 *********************************************************************/
#ifndef SPACESHOOTER_GAMESTATE_H_
    #define SPACESHOOTER_GAMESTATE_H_

#include <vector>
#include "ApplicationState.h"
#include "BlackScreen.h"
#include "GameEntityManager.h"

class GameEntity;

class GameState : public ApplicationState
{
    private:
        SDL_Event event;
        BlackScreen blackScreen;

        GameEntityManager gameEntityManager;
        GameEntity* background;
        GameEntity* player;
        GameEntity* meteor;
        std::vector<GameEntity*> enemies;

        int nextState;
        int pauseStatus;

        Level level;

    public:
        //Constructor
        GameState(ApplicationStateManager* applicationStateManager,
                  WindowElements* windowElements);

        //Destructor
        ~GameState();

        //GameState methods
        void onEnter();
        void onEvent();
        void onUpdate();
        void onRender();
        void onExit();
        void stateTransition(int nextState);
        void setPauseStatus(int pauseStatus);
};

#endif
