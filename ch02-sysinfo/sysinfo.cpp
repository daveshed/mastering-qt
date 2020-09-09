#include <cassert>

#include "sysinfo.h"
#include "sysinfolinuximpl.h"

SysInfo::SysInfo()
{
    // empty constructor as this is a singleton. There is only one instance
    // which is accessed through the getter.
}

SysInfo::~SysInfo()
{
    // singletons can't be destroyed.
}

SysInfo& SysInfo::instance()
{
    // TODO: implement other os specific stuff.
    #ifndef Q_OS_LINUX
        assert(0);
    #endif
    // static variable only initialised once...
    static SysInfoLinuxImpl singleton;
    return singleton;
}
