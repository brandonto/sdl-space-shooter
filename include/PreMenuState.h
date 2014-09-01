/*******************************************************************//*
 * This is the ApplicationState class for the pre main menu screen. This
 * state is entered in between the intro state and menu state at the
 * beginning
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-31
 * @modified    2014-08-31
 *********************************************************************/
#ifndef SPACESHOOTER_PREMENUSTATE_H_
    #define SPACESHOOTER_PREMENUSTATE_H_

#include "ApplicationState.h"
#include "GameEntityManager.h"

class PreMenuState : public ApplicationState
{
    private:
        SDL_Event event;
        GameEntityManager gameEntityManager;

    public:
        //Constructor
        PreMenuState(ApplicationStateManager* applicationStateManager,
                     WindowElements* windowElements);

        //Destructor
        ~PreMenuState();

        //GameState methods
        void onEnter();
        void onEvent();
        void onUpdate();
        void onRender();
        void onExit();
};

#endif
