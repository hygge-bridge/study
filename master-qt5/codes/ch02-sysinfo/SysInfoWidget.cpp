#include <QVBoxLayout>
#include "SysInfoWidget.h"

SysInfoWidget::SysInfoWidget(QWidget *parent, int startDelayMs, int intervalDelayMs)
    : QWidget(parent)
    , mTimer()
    , mChartView(new QtCharts::QChartView(this))
{
    mTimer.setInterval(intervalDelayMs);
    connect(&mTimer, &QTimer::timeout, this, &SysInfoWidget::updateSeries);
    mTimer.start(startDelayMs);

    mChartView->setRenderHint(QPainter::Antialiasing);
    mChartView->chart()->legend()->setVisible(false);

    setLayout(new QVBoxLayout());
    layout()->addWidget(mChartView);
}

SysInfoWidget::~SysInfoWidget() = default;
