#include <windows.h>
#include <pdh.h>
#include <pdhmsg.h>
#include "SysInfoWinImpl.h"

class SysInfoWinImpl::SysMonitor
{
public:
    explicit SysMonitor()
        : mCpuQuery(nullptr)
        , mCpuTotal(nullptr)
    {

    }

    ~SysMonitor()
    {
        if (mCpuQuery) {
            PdhCloseQuery(mCpuQuery);
        }
    }

    void init()
    {
        PdhOpenQuery(nullptr, 0, &mCpuQuery);
        PdhAddCounter(mCpuQuery, L"\\Processor(_Total)\\% Processor Time", 0, &mCpuTotal);
        PdhCollectQueryData(mCpuQuery);
    }

    double cpuLoaded()
    {
        PDH_FMT_COUNTERVALUE counterVal;
        PdhCollectQueryData(mCpuQuery);
        if (PdhGetFormattedCounterValue(mCpuTotal, PDH_FMT_DOUBLE, nullptr, &counterVal) == ERROR_SUCCESS) {
            return counterVal.doubleValue;
        }
        return 0.0;
    }

    double memoryUsed()
    {
        MEMORYSTATUSEX memInfo;
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);
        if (GlobalMemoryStatusEx(&memInfo)) {
            DWORDLONG usedMemory = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
            double usagePercentage = (static_cast<double>(usedMemory) /
                                     static_cast<double>(memInfo.ullTotalPhys)) * 100.0;
            return usagePercentage;
        }
        return 0.0;
    }

private:
    PDH_HQUERY mCpuQuery;
    PDH_HCOUNTER mCpuTotal;
};

SysInfoWinImpl::SysInfoWinImpl()
    : mSysMonitor(std::make_unique<SysMonitor>())
{

}

SysInfoWinImpl::~SysInfoWinImpl() = default;


void SysInfoWinImpl::init()
{
    mSysMonitor->init();
}

double SysInfoWinImpl::cpuLoaded() const
{
    return mSysMonitor->cpuLoaded();
}

double SysInfoWinImpl::memoryUsed() const
{
    return mSysMonitor->memoryUsed();
}
