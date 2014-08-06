#include <SDL2/SDL.h>
#include "Application.h"

/*******************************************************************//*
 * The main function. Creates and runs Application class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-08-05
 *********************************************************************/

int main(int argc, char* argv[])
{
    Application application;

    return application.start();
}
