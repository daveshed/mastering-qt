#include "Task.h"
#include "ui_Task.h"

Task::Task(const QString& name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);
    setName(name);
}

void Task::setName(const QString &name)
{
    ui->checkbox->setText(name);
}

QString Task::name(void) const
{
    return ui->checkbox->text();
}

bool Task::isCompleted(void) const
{
    return ui->checkbox->isChecked();
}

Task::~Task()
{
    delete ui;
}
