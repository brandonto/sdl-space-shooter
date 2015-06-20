/*******************************************************************//*
 * The main function. Creates and runs Application class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-08-20
 *********************************************************************/
#include "Application.h"
#undef main

int main(int argc, char* argv[])
{
    Application application;

    return application.start();
}
