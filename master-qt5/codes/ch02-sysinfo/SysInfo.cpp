#include <QtGlobal>
#include "SysInfo.h"

#ifdef Q_OS_WIN
    #include "SysInfoWinImpl.h"
#endif

SysInfo &SysInfo::instance()
{
#ifdef Q_OS_WIN
    static SysInfoWinImpl instance;
#endif
    return instance;
}

SysInfo::SysInfo()
{

}
