#ifndef CPUWIDGET_H
#define CPUWIDGET_H

#include <QPieSeries>
#include "SysInfoWidget.h"

class SysInfo;

class CpuWidget : public SysInfoWidget
{
    Q_OBJECT
public:
    explicit CpuWidget(QWidget* parent = nullptr);

protected slots:
    void updateSeries() override;

private:
    SysInfo& mSysInfo;
    QtCharts::QPieSeries* mSeries;
};

#endif // CPUWIDGET_H
