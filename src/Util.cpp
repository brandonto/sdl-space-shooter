/*******************************************************************//*
 * Several useful utility functions wrapped in a namespace
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-18
 * @modified    2015-02-18
 *********************************************************************/
#include "Util.h"

#include <cstdio>
#include <libgen.h>

#ifdef _WIN32
    #include <windows.h>
#endif

#ifdef linux
    #include <unistd.h>
#endif

namespace Util
{
    std::string fix_path(std::string path)
    {
#ifdef _WIN32
        // Creates a path to the binary location
        char buf[256];
        GetModuleFileName(NULL, buf, sizeof(buf)-1);
        std::string binaryLocation = dirname(buf);
        return binaryLocation + "/../" + path;
#endif

#ifdef linux
        // Creates a path to the binary location
        char buf[256];
        readlink("/proc/self/exe", buf, sizeof(buf)-1);
        std::string binaryLocation = dirname(buf);
        return binaryLocation + "/" + path;
#endif
    }
}
