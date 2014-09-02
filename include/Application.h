/*******************************************************************//*
 * Core Application class. Initializes and closes SDL and contains the
 * main game loop.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-09-01
 *********************************************************************/
#ifndef SPACESHOOTER_APPLICATION_H_
    #define SPACESHOOTER_APPLICATION_H_

#include "WindowElements.h"
//#include "ApplicationStateManager.h"
class ApplicationStateManager;

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
        void terminate();
};

#endif
