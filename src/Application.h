#ifndef _APPLICATION_H_
    #define _APPLICATION_H_

/*******************************************************************//*
 * Core Application class. Initializes and closes SDL and contains the
 * main game loop.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-08-05
 *********************************************************************/

class Application
{
    private:
        //Fields
        SDL_Window* gameWindow;
        SDL_Surface* gameScreen;
        ApplicationStateManager* applicationStateManager;

    public:
        //Constructor
        Application();

        //Destructor
        ~Application();

        //Methods
        int start();
        bool initialize();
};

#endif
