#include "MainWindow.h"
#include "SysInfo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SysInfo::instance().init();
    MainWindow w;
    w.show();
    return a.exec();
}
