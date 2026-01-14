#include <QAreaSeries>
#include "MemoryWidget.h"
#include "SysInfo.h"

const int AXES_X_RANGE = 50;
const int AXES_X_MAX = AXES_X_RANGE - 1;
const int AXES_Y_RANGE = 100;
const int AXES_Y_MAX = AXES_Y_RANGE - 1;

MemoryWidget::MemoryWidget(QWidget* parent)
    : SysInfoWidget(parent)
    , mSysInfo(SysInfo::instance())
    , mSeries(new QtCharts::QLineSeries(this))
    , mLastPosition(0)
{
    mSeries->append(0, 0);
    QtCharts::QAreaSeries* areaSeries = new QtCharts::QAreaSeries(mSeries);
    areaSeries->setName("Memory Used");

    QPen pen(0x059605);
    pen.setWidth(3);
    areaSeries->setPen(pen);
    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
    gradient.setColorAt(0.0, 0x3cc63c);
    gradient.setColorAt(1.0, 0x26f626);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    areaSeries->setBrush(gradient);

    QtCharts::QChart* chart = chartView().chart();
    chart->addSeries(areaSeries);
    chart->setTitle("Memory Used");
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setVisible(false);
    chart->axes(Qt::Horizontal).first()->setRange(0, AXES_X_MAX);
    chart->axes(Qt::Vertical).first()->setRange(0, AXES_Y_MAX);
}

void MemoryWidget::updateSeries()
{
    double memoryUsed = mSysInfo.memoryUsed();
    mSeries->append(mLastPosition++, memoryUsed);
    if (mSeries->count() > AXES_X_RANGE) {
        QtCharts::QChart* chart = chartView().chart();
        chart->scroll(chart->plotArea().width() / AXES_X_MAX, 0);
        mSeries->remove(0);
    }
}
