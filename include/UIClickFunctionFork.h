/*******************************************************************//*
 * This class encapsulates a function called on UI Fork click.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-01
 * @modified    2015-02-01
 *********************************************************************/
#ifndef SPACESHOOTER_UICLICKFUNCTIONFORK_
    #define SPACESHOOTER_UICLICKFUNCTIONFORK_

#include "UIClickFunction.h"

class ApplicationState;

class UIClickFunctionFork : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        //Constructor
        UIClickFunctionFork(ApplicationState* state);

        //Methods
        void onClick();
};

#endif
