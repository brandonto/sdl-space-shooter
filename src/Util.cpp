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


#ifdef _WIN32
    #include <windows.h>
#endif

#ifdef __linux
    #include <unistd.h>
    #include <libgen.h>
#endif

#ifdef _WIN32
std::string dirname(const std::string& fname)
{
    size_t pos = fname.find_last_of("\\/");
    return (std::string::npos == pos)
        ? ""
        : fname.substr(0, pos);
}
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

#ifdef __linux
        // Creates a path to the binary location
        char buf[256];
        readlink("/proc/self/exe", buf, sizeof(buf)-1);
        std::string binaryLocation = dirname(buf);
        return binaryLocation + "/" + path;
#endif
    }
}
