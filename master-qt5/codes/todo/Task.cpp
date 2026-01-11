#include <QInputDialog>
#include <QFont>
#include <QCheckBox>
#include "Task.h"
#include "ui_Task.h"

Task::Task(const QString &name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);
    setName(name);
    connect(ui->editButton, &QPushButton::clicked, this, &Task::rename);
    connect(ui->removeButton, &QPushButton::clicked, [this]{
        emit remove(this);
    });
    connect(ui->checkbox, &QCheckBox::toggled, this, &Task::checked);
}

Task::~Task()
{
    delete ui;
}

void Task::setName(const QString &name)
{
    ui->checkbox->setText(name);
}

QString Task::name() const
{
    return ui->checkbox->text();
}

bool Task::isCompleted() const
{
    return ui->checkbox->isChecked();
}

void Task::rename()
{
    bool ok = false;
    QString name = QInputDialog::getText(this, tr("Rename"), tr("Type a new name"), QLineEdit::Normal, tr("a new name"), &ok);
    if (ok && !name.isEmpty()) {
        setName(name);
    }
}

void Task::checked(bool isChecked)
{
    QFont font = ui->checkbox->font();
    font.setStrikeOut(isChecked);
    ui->checkbox->setFont(font);
    emit statusChanged(this);
}
