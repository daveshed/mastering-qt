#include <QDebug>
#include <QInputDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mTasks()

{
    ui->setupUi(this);
    connect(
        ui->addTaskButton,
        &QPushButton::clicked,
        this,
        &MainWindow::addTask);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask()
{
    bool ok;
    QString name = QInputDialog::getText(
                this,
                tr("Add task"),
                tr("Task name"),
                QLineEdit::Normal,
                tr("Untitled task"),
                &ok);
    if (ok && !name.isEmpty())
    {
        qDebug() << "Adding a new task..." << name;
        Task* task = new Task(name);
        mTasks.append(task);
        connect(
            task,
            &Task::removed,
            this,
            &MainWindow::removeTask);
        ui->tasksLayout->addWidget(task);
    }
}

void MainWindow::removeTask(Task* task)
{
    qDebug() << "Removing task... " << task->name();
    mTasks.removeOne(task);
    ui->tasksLayout->removeWidget(task);
    delete task;
}
