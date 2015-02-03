/*******************************************************************//*
 * This astract class encapsulates a function called on UI click
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-04
 * @modified    2015-02-03
 *********************************************************************/
#ifndef SPACESHOOTER_UICLICKFUNCTION_
    #define SPACESHOOTER_UICLICKFUNCTION_

#include <stdlib.h>
#include <string>
#include "ApplicationState.h"

//namespace UIClickFunction
//{
//    enum Functions
//    {
//        //Click Functions
//        FUNCTION_BACK,
//        FUNCTION_CREDITS,
//        FUNCTION_FORK,
//        FUNCTION_INSTRUCTIONS,
//        FUNCTION_MENU,
//        FUNCTION_PLAY,
//        FUNCTION_QUIT,
//        FUNCTION_RESUME,
//    };
//}

class UIClickFunction
{
    public:
        //Destructor
        virtual ~UIClickFunction(){};

        //Must override virtual method
        virtual void onClick() = 0;
};

class UIClickFunctionBack : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        UIClickFunctionBack(ApplicationState* state) : state(state) {};

        void onClick() { state->stateTransition(STATE_MENU); }
};

class UIClickFunctionCredits : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        UIClickFunctionCredits(ApplicationState* state) : state(state) {};

        void onClick() { state->stateTransition(STATE_CREDITS); }
};

class UIClickFunctionFork : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        UIClickFunctionFork(ApplicationState* state) : state(state) {};

        void onClick() {
            std::string url = "xdg-open https://github.com/brandonto/sdl-space-shooter";
            system(url.c_str());
            //Windows Only
            //ShellExecute(NULL, "open", "https://github.com/brandonto/sdl-space-shooter",
            //            NULL, NULL, SW_SHOWNORMAL);
        }
};

class UIClickFunctionInstructions : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        UIClickFunctionInstructions(ApplicationState* state) : state(state) {};

        void onClick() { state->stateTransition(STATE_INSTRUCTIONS); }
};

class UIClickFunctionMenu : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        UIClickFunctionMenu(ApplicationState* state) : state(state) {};

        void onClick() { state->stateTransition(STATE_MENU); }
};

class UIClickFunctionPlay : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        UIClickFunctionPlay(ApplicationState* state) : state(state) {};

        void onClick() { state->stateTransition(STATE_GAME); }
};

class UIClickFunctionQuit : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        //Constructor
        UIClickFunctionQuit(ApplicationState* state) : state(state) {};

        //Methods
        void onClick() { state->stateTransition(STATE_EXIT); }
};

class UIClickFunctionResume : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        //Constructor
        UIClickFunctionResume(ApplicationState* state) : state(state) {};

        //Methods
        void onClick() { state->onExit(); }
};

#endif
