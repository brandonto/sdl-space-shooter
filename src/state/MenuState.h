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
 * @modified    2014-08-06
 *********************************************************************/

class MenuState : public ApplicationState
{
    private:

    public:
        //Constructor
        MenuState(WindowElements* windowElements);

        //Destructor
        ~MenuState();

        //GameState methods
        //void onEnter();
        void onEvent();
        void onUpdate();
        void onRender();
        //void onExit();
};

#endif
