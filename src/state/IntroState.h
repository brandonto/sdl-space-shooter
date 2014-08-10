/*******************************************************************//*
 * This is the GameState class for the introduction screen. This state
 * occurs once at the beginning of program execution.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-08-10
 *********************************************************************/
#ifndef _INTROSTATE_H
    #define _INTROSTATE_H

#include "ApplicationState.h"

class IntroState : public ApplicationState
{
    private:
        //Fields

    public:
        //Constructor
        IntroState();

        //Destructor
        ~IntroState();

        //GameState methods
        //void onEnter();
        void onEvent();
        void onUpdate();
        void onRender();
        //void onExit();
};

#endif
