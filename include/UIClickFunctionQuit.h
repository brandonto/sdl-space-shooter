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

class ApplicationState;

class UIClickFunctionQuit : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        //Constructor
        UIClickFunctionQuit(ApplicationState* state);

        //Methods
        void onClick();
};

#endif
