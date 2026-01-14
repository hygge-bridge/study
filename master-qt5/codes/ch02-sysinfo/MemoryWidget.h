#ifndef MEMORYWIDGET_H
#define MEMORYWIDGET_H

#include <QLineSeries>
#include "SysInfoWidget.h"

class SysInfo;

class MemoryWidget : public SysInfoWidget
{
    Q_OBJECT
public:
    explicit MemoryWidget(QWidget* parent = nullptr);

protected slots:
    void updateSeries() override;

private:
    SysInfo& mSysInfo;
    QtCharts::QLineSeries* mSeries;
    uint64_t mLastPosition;
};

#endif // MEMORYWIDGET_H
