#ifndef MEMORYWIDGET_H
#define MEMORYWIDGET_H
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLineSeries>

#include "sysinfowidget.h"

using namespace QtCharts;

class MemoryWidget : public SysInfoWidget
{
    Q_OBJECT
public:
    explicit MemoryWidget(QWidget *parent = 0);

protected slots:
    void updateSeries() override;

private:
    QLineSeries* mSeries;
    qint64 mPointPositionX;

private:
    void configureAreaSeries(QAreaSeries*);
    void configureChart(QChart*);
};

#endif // MEMORYWIDGET_H
