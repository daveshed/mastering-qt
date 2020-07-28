#ifndef TASK_H
#define TASK_H

#include <QWidget>

namespace Ui {
class Task;
}

class Task : public QWidget
{
    Q_OBJECT

public:
    explicit Task(const QString& name, QWidget *parent = nullptr);
    ~Task();

    void setName(const QString& name);
    QString name(void) const;
    bool isCompleted(void) const;

private:
    Ui::Task *ui;
};

#endif // TASK_H
