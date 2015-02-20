/*******************************************************************//*
 * This class encapsulates a function called on UI click
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-04
 * @modified    2015-02-20
 *********************************************************************/
#ifndef SPACESHOOTER_UICLICKFUNCTION_
    #define SPACESHOOTER_UICLICKFUNCTION_

#include <map>
#include <stdlib.h>
#include <string>
#include "ApplicationState.h"

struct WindowElements;

class UIClickFunction
{
    private:
        ApplicationState* state;
        WindowElements* windowElements;
        std::map<std::string, void(*)(ApplicationState*, WindowElements*)> functionTable;
        void (*callback)(ApplicationState*, WindowElements*);

    public:
        //Constructor
        UIClickFunction(ApplicationState* state,
                        WindowElements* windowElements);

        //Destructor
        ~UIClickFunction();

        void setCallback(std::string callback);
        virtual void onClick();
};

#endif
