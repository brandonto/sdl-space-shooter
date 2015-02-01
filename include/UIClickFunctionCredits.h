/*******************************************************************//*
 * This class encapsulates a function called on UI Credits click.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-01
 * @modified    2015-02-01
 *********************************************************************/
#ifndef SPACESHOOTER_UICLICKFUNCTIONCREDITS_
    #define SPACESHOOTER_UICLICKFUNCTIONCREDITS_

#include "UIClickFunction.h"

class ApplicationState;

class UIClickFunctionCredits : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        //Constructor
        UIClickFunctionCredits(ApplicationState* state);

        //Methods
        void onClick();
};

#endif
