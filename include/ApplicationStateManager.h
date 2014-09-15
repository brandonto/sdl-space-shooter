/*******************************************************************//*
 * This class encapsulates all state code. Responsibilities include
 * keeping a pointer to current and previous states, switching states,
 * handling state transitions, and delegating game loop methods to
 * respective states.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-09-15
 *********************************************************************/
#ifndef SPACESHOOTER_APPLICATIONSTATEMANAGER_H_
    #define SPACESHOOTER_APPLICATIONSTATEMANAGER_H_

#include <vector>

class ApplicationState;
class WindowElements;

class ApplicationStateManager
{
    private:
        //Fields
        WindowElements* windowElements;
        ApplicationState* currentState;
        std::vector<ApplicationState*> stateStack;
        std::vector<int> stateStackEnum;
        int currentStateEnum;
        int nextStateEnum;
        int pushedStateEnum;
        bool popState;

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
        ApplicationState* getMainState();
        bool isExitState();
        void setNextState(int nextState);
        void pushStateOnStack(int pushedState);
        void popStateOnStack();
        void changeState();
};


#endif
