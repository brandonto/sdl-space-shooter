/*******************************************************************//*
 * This class encapsulates a function called on UI Instructions click.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-01-31
 * @modified    2015-01-31
 *********************************************************************/
#ifndef SPACESHOOTER_UICLICKFUNCTIONINSTRUCTIONS_
    #define SPACESHOOTER_UICLICKFUNCTIONINSTRUCTIONS_

#include "UIClickFunction.h"

class ApplicationState;

class UIClickFunctionInstructions : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        //Constructor
        UIClickFunctionInstructions(ApplicationState* state);

        //Methods
        void onClick();
};

#endif
