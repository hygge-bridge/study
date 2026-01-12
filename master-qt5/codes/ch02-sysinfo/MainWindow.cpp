#include <QHBoxLayout>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CpuWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mCpuWidget(new CpuWidget(this))
{
    ui->setupUi(this);
    centralWidget()->setLayout(new QHBoxLayout());
    centralWidget()->layout()->addWidget(mCpuWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

