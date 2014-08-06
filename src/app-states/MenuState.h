#ifndef _MENUSTATE_H_
    #define _MENUSTATE_H_

/*******************************************************************//*
 * This is the ApplicationState class for the main menu screen. This
 * state is entered after the intro state at the beginning and can be
 * navigated to from the pause state.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-08-05
 *********************************************************************/

class MenuState : public ApplicationState
{
    private:
        //Fields

    public:
        //Constructor
        MenuState();

        //Destructor
        ~MenuState();

        //GameState methods
        //void onEnter();
        void onEvent();
        void onLoop();
        void onRender();
        //void onExit();
};

#endif
