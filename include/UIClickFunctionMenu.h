/*******************************************************************//*
 * This class encapsulates a function called on UI Menu click.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-02
 * @modified    2015-02-02
 *********************************************************************/
#ifndef SPACESHOOTER_UICLICKFUNCTIONMENU_
    #define SPACESHOOTER_UICLICKFUNCTIONMENU_

#include "UIClickFunction.h"

class ApplicationState;

class UIClickFunctionMenu : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        //Constructor
        UIClickFunctionMenu(ApplicationState* state);

        //Methods
        void onClick();
};

#endif

