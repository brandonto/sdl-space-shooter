/*******************************************************************//*
 * This class encapsulates a function called on UI Play click.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-05
 * @modified    2014-09-05
 *********************************************************************/
#ifndef SPACESHOOTER_UICLICKFUNCTIONPLAY_
    #define SPACESHOOTER_UICLICKFUNCTIONPLAY_

#include "UIClickFunction.h"

class ApplicationState;

class UIClickFunctionPlay : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        //Constructor
        UIClickFunctionPlay(ApplicationState* state);

        //Methods
        void onClick();
};

#endif
