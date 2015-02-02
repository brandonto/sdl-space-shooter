/*******************************************************************//*
 * This class encapsulates a function called on UI Resume click.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-02
 * @modified    2015-02-02
 *********************************************************************/
#ifndef SPACESHOOTER_UICLICKFUNCTIONRESUME_
    #define SPACESHOOTER_UICLICKFUNCTIONRESUME_

#include "UIClickFunction.h"

class ApplicationState;

class UIClickFunctionResume : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        //Constructor
        UIClickFunctionResume(ApplicationState* state);

        //Methods
        void onClick();
};

#endif

