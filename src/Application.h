#ifndef _APPLICATION_H_
    #define _APPLICATION_H_

/*******************************************************************//*
 * Core Application class. Initializes and closes SDL and contains the
 * main game loop.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-08-06
 *********************************************************************/

class Application
{
    private:
        //Fields
        WindowElements windowElements;
        ApplicationStateManager* applicationStateManager;
        bool quit;

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
