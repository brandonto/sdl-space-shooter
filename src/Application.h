#ifndef _APPLICATION_H_
    #define _APPLICATION_H_

#include "WindowElements.h"
#include "state/ApplicationStateManager.h"

/*******************************************************************//*
 * Core Application class. Initializes and closes SDL and contains the
 * main game loop.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-08-07
 *********************************************************************/

class Application
{
    private:
        //Fields
        WindowElements windowElements;
        ApplicationStateManager* applicationStateManager;

    public:
        //Constructor
        Application();

        //Destructor
        ~Application();

        //Methods
        int start();
        bool initialize();
        bool terminate();
};

#endif
