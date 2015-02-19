/*******************************************************************//*
 * This is the ApplicationState class for the game. This state is
 * entered after clicking the "Play" button from the menu state
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-05
 * @modified    2015-02-18
 *********************************************************************/
#ifndef SPACESHOOTER_GAMESTATE_H_
    #define SPACESHOOTER_GAMESTATE_H_

#include <vector>
#include "ApplicationState.h"
#include "BlackScreen.h"
#include "GameEntityManager.h"
#include "IObserver.h"

class GameEntity;

class GameState : public ApplicationState,
                    public IObserver
{
    private:
        SDL_Event event;
        BlackScreen blackScreen;

        GameEntityManager gameEntityManager;
        GameEntity* background;
        GameEntity* player;
        std::vector<GameEntity*> enemies;
        GameEntity* uiLives;
        GameEntity* uiScore;

        int nextState;
        int pauseStatus;

        Level level;

        int lives;
        bool playerDestroyed;

        int score;

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

        //IObserver virtual methods
        void onNotify(GameEntity* entity, int event);
};

enum observingEvents
{
    PLAYER_DESTROYED,
    ENEMY_DESTROYED,
};


#endif
