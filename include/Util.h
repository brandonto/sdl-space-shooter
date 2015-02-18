/*******************************************************************//*
 * Several useful utility functions wrapped in a namespace
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-18
 * @modified    2015-02-18
 *********************************************************************/
#ifndef SPACESHOOTER_UTIL_H_
    #define SPACESHOOTER_UTIL_H_

#include <string>

namespace Util
{
    // This method appends the location of the binary/executable file
    // to the argument
    std::string fix_path(std::string path);
}

#endif

