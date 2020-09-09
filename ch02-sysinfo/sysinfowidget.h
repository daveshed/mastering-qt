#ifndef SYSINFOWIDGET_H
#define SYSINFOWIDGET_H
#include <QtCharts/QChartView>
#include <QTimer>
#include <QWidget>

class SysInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SysInfoWidget(
        QWidget* parent = Q_NULLPTR,
        int startDelayMs = 500,
        int updateSeriesDelayMs = 500);

protected:
    QtCharts::QChartView& chartView();

protected slots:
    virtual void updateSeries() = 0;

private:
    QTimer mRefreshTimer;
    QtCharts::QChartView mChartView;
};

#endif // SYSINFOWIDGET_H
