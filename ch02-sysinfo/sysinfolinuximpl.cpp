#include <sys/types.h>
#include <sys/sysinfo.h>

#include <QFile>
#include <QtDebug>
#include <QtGlobal>
#include <QVector>

#include "sysinfolinuximpl.h"

SysInfoLinuxImpl::SysInfoLinuxImpl() :
    SysInfo(),
    mCpuLoadLastValues()
{
}

void SysInfoLinuxImpl::init()
{
    mCpuLoadLastValues = cpuRawData();
}

double SysInfoLinuxImpl::cpuLoadAverage()
{
    QVector<qulonglong> firstSample = mCpuLoadLastValues;
    QVector<qulonglong> secondSample = cpuRawData();
    double overall = (secondSample[0] - firstSample[0])
        + (secondSample[1] - firstSample[1])
        + (secondSample[2] - firstSample[2]);
    double total = overall + (secondSample[3] - firstSample[3]);
    double percent = (overall / total) * 100.0;
    return qBound(0.0, percent, 100.);
}

double SysInfoLinuxImpl::memoryUsed()
{
    struct sysinfo memInfo;  // what's going on here?!
    sysinfo(&memInfo);
    qulonglong totalMemory = memInfo.totalram;
    totalMemory += memInfo.totalswap;
    totalMemory *= memInfo.mem_unit;

    qulonglong totalMemoryUsed = (memInfo.totalram - memInfo.freeram);
    totalMemoryUsed += (memInfo.totalswap - memInfo.freeswap);
    totalMemoryUsed *= memInfo.mem_unit;

    double percent = (double)totalMemoryUsed / (double)totalMemory * 100.0;
    qDebug() << "Memory used... " << percent << "%";
    return qBound(0.0, percent, 100.0);
}

// PRIVATE
QVector<qulonglong> SysInfoLinuxImpl::cpuRawData()
{
    QFile file("/proc/stat");
    file.open(QIODevice::ReadOnly);
    QByteArray line = file.readLine();
    qDebug() << "Read /proc/stat.." << line;
    file.close();
    qulonglong totalUser = 0;
    qulonglong totalUserNice = 0;
    qulonglong totalSystem = 0;
    qulonglong totalIdle = 0;
    std::sscanf(
        line.data(),
        "cpu %11u %11u %11u %11u",
        &totalUser,
        &totalUserNice,
        &totalSystem,
        &totalIdle);
    // FIXME: this should be a custom typedef of struct
    QVector<qulonglong> rawData;
    rawData.append(totalUser);
    rawData.append(totalUserNice);
    rawData.append(totalSystem);
    rawData.append(totalIdle);
    qDebug() << "Returning raw data... " << rawData;
    return rawData;
}
