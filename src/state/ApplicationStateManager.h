#ifndef _APPLICATIONSTATEMANAGER_H_
    #define _APPLICATIONSTATEMANAGER_H_

#include "ApplicationState.h"
#include "../WindowElements.h"

/*******************************************************************//*
 * This class encapsulates all state code. Responsibilities include
 * keeping a pointer to current and previous states, switching states,
 * handling state transitions, and delegating game loop methods to
 * respective states.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-08-07
 *********************************************************************/

class ApplicationStateManager
{
    private:
        //Fields
        WindowElements* windowElements;
        ApplicationState* currentState;
        int nextStateEnum;

    public:
        //Constructor
        ApplicationStateManager(WindowElements* windowElements);

        //Destructor
        ~ApplicationStateManager();

        //Methods
        void onEvent();
        void onUpdate();
        void onRender();
        ApplicationState* getCurrentState();
        bool isExit();
        void setNextState(int nextState);
        void changeState();
};


#endif
