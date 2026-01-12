#ifndef SYSINFOWIDGET_H
#define SYSINFOWIDGET_H

#include <QWidget>
#include <QTimer>

namespace QtCharts {
    class QChartView;
}

class SysInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SysInfoWidget(QWidget *parent = nullptr, int startDelayMs = 100, int intervalDelayMs = 500);
    ~SysInfoWidget();

protected slots:
    virtual void updateSeries() = 0;

protected:
    QtCharts::QChartView& chartView();

private:
    QTimer mTimer;
    QtCharts::QChartView* mChartView;
};

#endif // SYSINFOWIDGET_H
