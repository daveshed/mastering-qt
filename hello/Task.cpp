#include <QDebug>
#include <QInputDialog>

#include "Task.h"
#include "ui_Task.h"

Task::Task(const QString& name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);
    setName(name);
    connect(
        ui->editButton,
        &QPushButton::clicked,
        this,
        &Task::rename);
    connect(
        ui->removeButton,
        &QPushButton::clicked,
        [this, name]{
            qDebug() << "Trying to remove... " << name;
            emit removed(this);
        });
    connect(
        ui->checkbox,
        &QCheckBox::toggled,
        this,
        &Task::checked);
}

void Task::setName(const QString &name)
{
    ui->checkbox->setText(name);
}

void Task::rename()
{
    bool ok;
    QString result = QInputDialog::getText(
        this,
        tr("Edit task"),    //title
        tr("Task name"),    //label
        QLineEdit::Normal,
        this->name(),       //text
        &ok);
    if (ok && !result.isEmpty())
    {
        qDebug() << "Got name " << result;
        setName(result);
    }
}

QString Task::name(void) const
{
    return ui->checkbox->text();
}

bool Task::isCompleted(void) const
{
    return ui->checkbox->isChecked();
}

void Task::checked(bool checked)
{
    QFont font(ui->checkbox->font());
    font.setStrikeOut(checked);
    ui->checkbox->setFont(font);
    emit statusChanged(this);
}

Task::~Task()
{
    delete ui;
}
