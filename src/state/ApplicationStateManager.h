/*******************************************************************//*
 * This class encapsulates all state code. Responsibilities include
 * keeping a pointer to current and previous states, switching states,
 * handling state transitions, and delegating game loop methods to
 * respective states.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-08-10
 *********************************************************************/
#ifndef _APPLICATIONSTATEMANAGER_H_
    #define _APPLICATIONSTATEMANAGER_H_

class ApplicationState;
class WindowElements;

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
        bool isExitState();
        void setNextState(int nextState);
        void changeState();
};


#endif
