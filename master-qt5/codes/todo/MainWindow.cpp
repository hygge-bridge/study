#include <QInputDialog>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Task.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);
    updateStatus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask()
{
    bool ok = false;
    QString name = QInputDialog::getText(this, tr("Add a task"), tr("Task name"), QLineEdit::Normal, tr("a task name"), &ok);
    if (ok && !name.isEmpty()) {
        Task* newTask = new Task(name);
        connect(newTask, &Task::remove, this, &MainWindow::removeTask);
        connect(newTask, &Task::statusChanged, this, &MainWindow::taskStatusChanged);
        mTasks.push_back(newTask);
        ui->taskLayout->addWidget(newTask);
        updateStatus();
    }
}

void MainWindow::removeTask(Task *task)
{
    mTasks.removeOne(task);
    ui->taskLayout->removeWidget(task);
    delete task;
    updateStatus();
}

void MainWindow::taskStatusChanged(Task *task)
{
    Q_UNUSED(task);
    updateStatus();
}

void MainWindow::updateStatus()
{
    int hasCompleted = 0;
    for (Task* task : mTasks) {
        if (task->isCompleted()) {
            ++hasCompleted;
        }
    }
    int hasNotCompleted = mTasks.size() - hasCompleted;
    ui->statusLabel->setText(QString("Status: %1 todo / %2 done").arg(hasNotCompleted).arg(hasCompleted));
}

