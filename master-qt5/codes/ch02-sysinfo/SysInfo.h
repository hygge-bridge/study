#ifndef SYSINFO_H
#define SYSINFO_H


class SysInfo
{
public:
    static SysInfo& instance();
    virtual ~SysInfo() = default;

    virtual void init() = 0;
    virtual double cpuLoaded() const = 0;
    virtual double memoryUsed() const = 0;

protected:
    explicit SysInfo();

private:
    SysInfo(const SysInfo&) = delete;
    SysInfo& operator=(const SysInfo&) = delete;
};

#endif // SYSINFO_H
