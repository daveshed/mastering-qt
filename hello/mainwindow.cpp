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
    updateStatus();
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
        connect(
            task,
            &Task::statusChanged,
            this,
            &MainWindow::taskStatusChanged);
        ui->tasksLayout->addWidget(task);
        updateStatus();
    }
}

void MainWindow::removeTask(Task* task)
{
    qDebug() << "Removing task... " << task->name();
    mTasks.removeOne(task);
    ui->tasksLayout->removeWidget(task);
    delete task;
    updateStatus();
}

void MainWindow::taskStatusChanged(Task* /*task*/)
{
    updateStatus();
}

// PRIVATE
void MainWindow::updateStatus()
{
    int completedCount = 0;
    for (auto task : mTasks)
    {
        if (task->isCompleted())
        {
            completedCount++;
        }
    }
    int todoCount = mTasks.size() - completedCount;
    ui->statusLabel->setText(
        QString("Status: %1 todo / %2 completed")
            .arg(todoCount)
            .arg(completedCount));
}
