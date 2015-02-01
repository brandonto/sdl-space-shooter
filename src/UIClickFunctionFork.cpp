/*******************************************************************//*
 * Implementation of the UIClickFunctionFork class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-01
 * @modified    2015-02-01
 *********************************************************************/
#include "UIClickFunctionFork.h"

#include <stdlib.h>
#include <string>
#include "ApplicationState.h"

UIClickFunctionFork::UIClickFunctionFork(ApplicationState* state)
:   state(state)
{

}

void UIClickFunctionFork::onClick()
{
    std::string url = "xdg-open https://github.com/brandonto/sdl-space-shooter";
    system(url.c_str());
    //Windows Only
    //ShellExecute(NULL, "open", "https://github.com/brandonto/sdl-space-shooter",
    //            NULL, NULL, SW_SHOWNORMAL);
}
