#include <Qt>
#include <QtCharts/QAreaSeries>
#include <QLinearGradient>
#include <QPen>

#include "memorywidget.h"
#include "sysinfo.h"

using namespace QtCharts;

// these should belong to the class ie live in the header. You shouldn't need
// to peek into the implementation to change this.
const int CHART_X_RANGE_COUNT = 50;
const int CHART_X_RANGE_MAX = CHART_X_RANGE_COUNT - 1;
const int COLOUR_DARK_BLUE = 0x209fdf;
const int COLOUR_LIGHT_BLUE = 0xbfdfef;
const int PEN_WIDTH = 3;

MemoryWidget::MemoryWidget(QWidget* parent) :
    SysInfoWidget(parent),
    mSeries(new QLineSeries(this)),
    mPointPositionX(0)
{
    QAreaSeries* areaSeries = new QAreaSeries(mSeries);
    configureAreaSeries(areaSeries);
    QChart* chart = chartView().chart();
    chart->addSeries(areaSeries);
    configureChart(chart);
}

void MemoryWidget::updateSeries()
{
    double memoryUsed = SysInfo::instance().memoryUsed();
    // this is a hack! mPointPosition has been made a 64bit int to stop it
    // from overflowing. Surely this should be avoided by shifting the points
    // and not the window?
    mSeries->append(mPointPositionX++, memoryUsed);
    if (mSeries->count() > CHART_X_RANGE_COUNT)
    {
        QChart* chart = chartView().chart();
        chart->scroll(chart->plotArea().width() / CHART_X_RANGE_MAX, 0);
        mSeries->remove(0);
    }
}

// PRIVATE

void MemoryWidget::configureAreaSeries(QAreaSeries* areaSeries)
{
    QPen pen(COLOUR_DARK_BLUE);
    pen.setWidth(PEN_WIDTH);
    QPointF bottomLeft = QPointF(0, 0);
    QPointF bottomRight = QPointF(0, 1);
    QLinearGradient gradient(bottomLeft, bottomRight);
    // note that coordinates are normalised
    gradient.setColorAt(1.0, COLOUR_DARK_BLUE);
    gradient.setColorAt(0.0, COLOUR_LIGHT_BLUE);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    areaSeries->setPen(pen);
    areaSeries->setBrush(gradient);
}

void MemoryWidget::configureChart(QChart* chart)
{
    chart->setTitle("Memory used");
    chart->createDefaultAxes();
    // code in the example is deprecated...
    QAbstractAxis* xAxis = chart->axes(Qt::Horizontal).first();
    QAbstractAxis* yAxis = chart->axes(Qt::Vertical).first();
    xAxis->setVisible(false);
    xAxis->setRange(0, CHART_X_RANGE_MAX);
    yAxis->setRange(0, 100);
}
