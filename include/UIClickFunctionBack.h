/*******************************************************************//*
 * This class encapsulates a function called on UI Back click.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-01
 * @modified    2015-02-01
 *********************************************************************/
#ifndef SPACESHOOTER_UICLICKFUNCTIONBACK_
    #define SPACESHOOTER_UICLICKFUNCTIONBACK_

#include "UIClickFunction.h"

class ApplicationState;

class UIClickFunctionBack : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        //Constructor
        UIClickFunctionBack(ApplicationState* state);

        //Methods
        void onClick();
};

#endif
