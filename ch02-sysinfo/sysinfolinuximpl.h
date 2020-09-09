#ifndef SYSINFOLINUXIMPL_H
#define SYSINFOLINUXIMPL_H
#include <QtGlobal>
#include <QVector>

#include "sysinfo.h"

class SysInfoLinuxImpl : public SysInfo
{
public:
    SysInfoLinuxImpl();
    void init() override;
    double cpuLoadAverage() override;
    double memoryUsed() override;

private: // methods
    QVector<qulonglong> cpuRawData();

private: // members
    QVector<qulonglong> mCpuLoadLastValues;
};

#endif // SYSINFOLINUXIMPL_H
