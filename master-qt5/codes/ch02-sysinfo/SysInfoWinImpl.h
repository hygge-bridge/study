#ifndef SYSINFOWINIMPL_H
#define SYSINFOWINIMPL_H

#include <memory>
#include "SysInfo.h"

class SysInfoWinImpl : public SysInfo
{
public:
    explicit SysInfoWinImpl();
    ~SysInfoWinImpl();

    void init() override;
    double cpuLoaded() override;
    double memoryUsed() override;

private:
    class SysMonitor;
    std::unique_ptr<SysMonitor> mSysMonitor;
};

#endif // SYSINFOWINIMPL_H
