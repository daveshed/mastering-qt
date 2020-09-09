#ifndef SYSINFO_H
#define SYSINFO_H


class SysInfo
{
public:
    static SysInfo& instance(); // single access point to singleton
    virtual ~SysInfo();         // virtual implies that this may be overriden
    virtual void init() = 0;    // why wouldn't this be done in the
                                // constructor? Is this the convention for
                                // singletons?
    virtual double cpuLoadAverage() = 0;
    virtual double memoryUsed() = 0;

protected:
    explicit SysInfo();

private:
    // remove copy and assignment operators...
    SysInfo(const SysInfo& rhs);
    SysInfo& operator=(const SysInfo& rhs);
};

#endif // SYSINFO_H
