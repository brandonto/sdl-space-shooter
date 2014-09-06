/*******************************************************************//*
 * Core Application class. Initializes and closes SDL and contains the
 * main game loop.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-09-06
 *********************************************************************/
#ifndef SPACESHOOTER_APPLICATION_H_
    #define SPACESHOOTER_APPLICATION_H_

#include "FrameRateManager.h"
#include "WindowElements.h"

class ApplicationStateManager;

class Application
{
    private:
        //Fields
        WindowElements windowElements;
        ApplicationStateManager* applicationStateManager;
        FrameRateManager fpsManager;

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
