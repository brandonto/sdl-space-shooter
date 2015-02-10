/*******************************************************************//*
 * This class encapsulates a function called on UI click
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-04
 * @modified    2015-02-09
 *********************************************************************/
#ifndef SPACESHOOTER_UICLICKFUNCTION_
    #define SPACESHOOTER_UICLICKFUNCTION_

#include <map>
#include <stdlib.h>
#include <string>
#include "ApplicationState.h"

class UIClickFunction
{
    private:
        ApplicationState* state;
        std::map<std::string, void(*)(ApplicationState*)> functionTable;
        void (*callback)(ApplicationState*);

    public:
        //Constructor
        UIClickFunction(ApplicationState* state);

        //Destructor
        ~UIClickFunction();

        void setCallback(std::string callback);
        virtual void onClick();
};

class UIClickFunctionBack : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        UIClickFunctionBack(ApplicationState* state) : UIClickFunction(state), state(state) {};

        void onClick() { state->stateTransition(STATE_MENU); }
};

class UIClickFunctionCredits : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        UIClickFunctionCredits(ApplicationState* state) : UIClickFunction(state), state(state) {};

        void onClick() { state->stateTransition(STATE_CREDITS); }
};

class UIClickFunctionFork : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        UIClickFunctionFork(ApplicationState* state) : UIClickFunction(state), state(state) {};

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
        UIClickFunctionInstructions(ApplicationState* state) : UIClickFunction(state), state(state) {};

        void onClick() { state->stateTransition(STATE_INSTRUCTIONS); }
};

class UIClickFunctionMenu : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        UIClickFunctionMenu(ApplicationState* state) : UIClickFunction(state), state(state) {};

        void onClick() { state->stateTransition(STATE_MENU); }
};

class UIClickFunctionPlay : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        UIClickFunctionPlay(ApplicationState* state) : UIClickFunction(state), state(state) {};

        void onClick() { state->stateTransition(STATE_GAME); }
};

class UIClickFunctionQuit : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        //Constructor
        UIClickFunctionQuit(ApplicationState* state) : UIClickFunction(state), state(state) {};

        //Methods
        void onClick() { state->stateTransition(STATE_EXIT); }
};

class UIClickFunctionResume : public UIClickFunction
{
    private:
        ApplicationState* state;

    public:
        //Constructor
        UIClickFunctionResume(ApplicationState* state) : UIClickFunction(state), state(state) {};

        //Methods
        void onClick() { state->onExit(); }
};

#endif
