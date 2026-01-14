#include <QHBoxLayout>
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mCpuWidget(new CpuWidget(this))
    , mMemoryWidget(new MemoryWidget(this))
{
    ui->setupUi(this);
    centralWidget()->setLayout(new QHBoxLayout());
    centralWidget()->layout()->addWidget(mCpuWidget);
    centralWidget()->layout()->addWidget(mMemoryWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

