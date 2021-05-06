#ifndef TODOMAIN_H
#define TODOMAIN_H
#include <QVector>
#include <QDialog>
#include "task.h"

namespace Ui {
class todomain;
}

class todomain : public QDialog
{
    Q_OBJECT

public:
    explicit todomain(QWidget *parent = 0);
    ~todomain();
    void updateStatus();
public slots:
    void addTask();
    void removeTask(Task *task);
    void taskStatusChanged(Task *task);

private:
    Ui::todomain *ui;
    QVector<Task*> mTasks;
};

#endif // TODOMAIN_H
