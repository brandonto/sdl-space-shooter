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
    #include <SDL.h>
    #include <windows.h>
#endif

#ifdef __linux
    #include <SDL2/SDL.h>
#endif

#include "ApplicationStateManager.h"
#include "AudioSystem.h"
#include "WindowElements.h"

namespace ClickFunctions
{
    void onClickBack(ApplicationState* state, WindowElements* windowElements)
    {
        state->statePop();
    }

    void onClickCredits(ApplicationState* state, WindowElements* windowElements)
    {
        state->statePush(STATE_CREDITS);
    }

    void onClickFork(ApplicationState* state, WindowElements* windowElements)
    {
#ifdef _WIN32
        std::string url = "https://github.com/brandonto/sdl-space-shooter";
        ShellExecute(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
#endif

#ifdef __linux
        std::string url = "xdg-open https://github.com/brandonto/sdl-space-shooter";
        system(url.c_str());
#endif
    }

    void onClickGame(ApplicationState* state, WindowElements* windowElements)
    {
        state->stateTransition(STATE_GAME);
    }

    void onClickInstructions(ApplicationState* state, WindowElements* windowElements)
    {
        state->statePush(STATE_INSTRUCTIONS);
    }

    void onClickMenu(ApplicationState* state, WindowElements* windowElements)
    {
        state->stateTransition(STATE_MENU);
    }

    void onClickMusic(ApplicationState* state, WindowElements* windowElements)
    {
        AudioSystem::getInstance()->toggleMusic();
    }

    void onClickNone(ApplicationState* state, WindowElements* windowElements)
    {
    }

    void onClickOptions(ApplicationState* state, WindowElements* windowElements)
    {
        state->statePush(STATE_OPTIONS);
    }

    void onClickQuit(ApplicationState* state, WindowElements* windowElements)
    {
        state->stateTransition(STATE_EXIT);
    }

    void onClickResume(ApplicationState* state, WindowElements* windowElements)
    {
        state->statePop();
    }

    void onClickSound(ApplicationState* state, WindowElements* windowElements)
    {
        AudioSystem::getInstance()->toggleSound();
    }

    void onClickWindow(ApplicationState* state, WindowElements* windowElements)
    {
        if (windowElements->fullScreen)
        {
            SDL_SetWindowFullscreen(windowElements->window, 0);
            windowElements->fullScreen = false;
        }
        else
        {
            SDL_SetWindowFullscreen(windowElements->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
            windowElements->fullScreen = true;
        }
    }
}

UIClickFunction::UIClickFunction(ApplicationState* state,
                            WindowElements* windowElements)
:   state(state),
    windowElements(windowElements)
{
    functionTable["BACK"] = &(ClickFunctions::onClickBack);
    functionTable["CREDITS"] = &(ClickFunctions::onClickCredits);
    functionTable["FORK"] = &(ClickFunctions::onClickFork);
    functionTable["GAME"] = &(ClickFunctions::onClickGame);
    functionTable["INSTRUCTIONS"] = &(ClickFunctions::onClickInstructions);
    functionTable["NONE"] = &(ClickFunctions::onClickNone);
    functionTable["MENU"] = &(ClickFunctions::onClickMenu);
    functionTable["MUSIC"] = &(ClickFunctions::onClickMusic);
    functionTable["OPTIONS"] = &(ClickFunctions::onClickOptions);
    functionTable["QUIT"] = &(ClickFunctions::onClickQuit);
    functionTable["RESUME"] = &(ClickFunctions::onClickResume);
    functionTable["SOUND"] = &(ClickFunctions::onClickSound);
    functionTable["WINDOW"] = &(ClickFunctions::onClickWindow);
    callback = functionTable["NONE"];
}

void UIClickFunction::setCallback(std::string callbackString)
{
    callback = functionTable[callbackString];
}

void UIClickFunction::onClick()
{
    callback(state, windowElements);
}

UIClickFunction::~UIClickFunction()
{
    // To be implemented
}

