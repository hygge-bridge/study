#include <QString>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include "CpuWidget.h"
#include "SysInfo.h"

const QString cpuUsedText = "Cpu Used";
const QString cpuFreeText = "Cpu Free";

CpuWidget::CpuWidget(QWidget *parent)
    : SysInfoWidget(parent)
    , mSysInfo(SysInfo::instance())
    , mSeries(new QtCharts::QPieSeries(this))
{
    mSeries->setName("Cpu Load");
    mSeries->setHoleSize(0.35);
    mSeries->append(cpuUsedText, 0);
    mSeries->append(cpuFreeText, 0);

    chartView().chart()->addSeries(mSeries);
}


void CpuWidget::updateSeries()
{
    double cpuUsed = mSysInfo.cpuLoaded();
    mSeries->clear();
    mSeries->append(cpuUsedText, cpuUsed);
    mSeries->append(cpuFreeText, 100.0 - cpuUsed);
}
