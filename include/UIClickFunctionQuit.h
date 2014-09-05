/*******************************************************************//*
 * This class encapsulates a function called on UI Quit click
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-05
 * @modified    2014-09-05
 *********************************************************************/
#ifndef SPACESHOOTER_UICLICKFUNCTIONQUIT_
    #define SPACESHOOTER_UICLICKFUNCTIONQUIT_

#include "UIClickFunction.h"

class ApplicationStateManager;

class UIClickFunctionQuit : public UIClickFunction
{
    private:
        ApplicationStateManager* stateManager;

    public:
        //Constructor
        UIClickFunctionQuit(ApplicationStateManager* stateManager);

        //Methods
        void onClick();
};

#endif
