#ifndef _APPLICATIONSTATEMANAGER_H_
    #define _APPLICATIONSTATEMANAGER_H_

/*******************************************************************//*
 * This class encapsulates all state code. Responsibilities include
 * keeping a pointer to current and previous states, switching states,
 * and handling state transitions.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-08-05
 *********************************************************************/

class ApplicationStateManager
{
    private:
        //Fields
        ApplicationState* applicationState;

    public:
        //Constructor
        ApplicationStateManager();

        //Destructor
        ~ApplicationStateManager();

        //Methods
        void setNextState();
        ApplicationState* getCurrentState();
};


#endif
