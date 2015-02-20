/*******************************************************************//*
 * Implementation of the UIClickFunction class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-09
 * @modified    2015-02-20
 *********************************************************************/
#include "UIClickFunction.h"

#ifdef _WIN32
    #include <windows.h>
#endif

#include "ApplicationStateManager.h"

namespace ClickFunctions
{
    void onClickBack(ApplicationState* state)
    {
        state->statePop();
    }

    void onClickCredits(ApplicationState* state)
    {
        state->statePush(STATE_CREDITS);
    }

    void onClickFork(ApplicationState* state)
    {
#ifdef _WIN32
        std::string url = "https://github.com/brandonto/sdl-space-shooter";
        ShellExecute(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
#endif

#ifdef linux
        std::string url = "xdg-open https://github.com/brandonto/sdl-space-shooter";
        system(url.c_str());
#endif
    }

    void onClickInstructions(ApplicationState* state)
    {
        state->statePush(STATE_INSTRUCTIONS);
    }

    void onClickMenu(ApplicationState* state)
    {
        state->stateTransition(STATE_MENU);
    }

    void onClickNone(ApplicationState* state)
    {
    }

    void onClickGame(ApplicationState* state)
    {
        state->stateTransition(STATE_GAME);
    }

    void onClickQuit(ApplicationState* state)
    {
        state->stateTransition(STATE_EXIT);
    }

    void onClickResume(ApplicationState* state)
    {
        state->onExit();
    }
}

UIClickFunction::UIClickFunction(ApplicationState* state)
:   state(state)
{
    functionTable["BACK"] = &(ClickFunctions::onClickBack);
    functionTable["CREDITS"] = &(ClickFunctions::onClickCredits);
    functionTable["FORK"] = &(ClickFunctions::onClickFork);
    functionTable["INSTRUCTIONS"] = &(ClickFunctions::onClickInstructions);
    functionTable["NONE"] = &(ClickFunctions::onClickNone);
    functionTable["MENU"] = &(ClickFunctions::onClickMenu);
    functionTable["GAME"] = &(ClickFunctions::onClickGame);
    functionTable["QUIT"] = &(ClickFunctions::onClickQuit);
    functionTable["RESUME"] = &(ClickFunctions::onClickResume);
    callback = functionTable["NONE"];
}

void UIClickFunction::setCallback(std::string callbackString)
{
    callback = functionTable[callbackString];
}

void UIClickFunction::onClick()
{
    callback(state);
}

UIClickFunction::~UIClickFunction()
{
    // To be implemented
}

