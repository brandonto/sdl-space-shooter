/*******************************************************************//*
 * This is the ApplicationState class for the pause screen. This state
 * is entered after pressing p at the game state.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-10
 * @modified    2014-09-15
 *********************************************************************/
#ifndef SPACESHOOTER_PAUSESTATE_H_
    #define SPACESHOOTER_PAUSESTATE_H_

#include <SDL2/SDL.h>
#include "ApplicationState.h"

class GameEntity;

class PauseState : public ApplicationState
{
    private:
        SDL_Event event;
        SDL_Texture* pausedText;
        SDL_Rect pausedTextRect;

    public:
        //Constructor
        PauseState(ApplicationStateManager* applicationStateManager,
                  WindowElements* windowElements);

        //Destructor
        ~PauseState();

        //GameState methods
        void onEnter();
        void onEvent();
        void onUpdate();
        void onRender();
        void onExit();
};

enum PauseStatuses
{
    PAUSED_NONE,
    PAUSED_THIS_FRAME,
    UNPAUSED_THIS_FRAME,
};

#endif
