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

#ifdef linux
    #include <libgen.h>
    #include <unistd.h>
#endif

namespace Util
{
    std::string fix_path(std::string path)
    {
#ifdef linux
        // Creates a path to the binary location
        char buf[256];
        readlink("/proc/self/exe", buf, sizeof(buf)-1);
        std::string binaryLocation = dirname(buf);
#endif

        return binaryLocation + "/" + path;
    }
}
