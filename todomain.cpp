#include "todomain.h"
#include "ui_todomain.h"
#include <QDebug>
#include <QInputDialog>

todomain::todomain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::todomain),
    mTasks()
{
    ui->setupUi(this);
    connect(ui->addTaskButton, &QPushButton::clicked,
            this, &todomain::addTask);
    // Call our method
    updateStatus();
}

todomain::~todomain()
{
    delete ui;
}

void todomain::addTask()
{
    bool ok;

    // Static blocking function that display dialog to get task name.
    /* Signature:
     * QString QInputDialog::getText(QWidget *parent, const QString &title, const QString &label,
     *                               QLineEdit::EchoMode mode = QLineEdit::Normal,
     *                               const QString &text = QString(),
     *                               bool *ok = 0, ...)
     */
    QString name = QInputDialog::getText(this,
                                         tr("Add task"),
                                         tr("Task name"),
                                         QLineEdit::Normal,
                                         tr("Untitled task"), &ok);
    if (ok && !name.isEmpty()) {
        qDebug() << "Adding new task";
        Task *task = new Task(name);
        connect(task, &Task::removed, this, &todomain::removeTask);
        connect(task, &Task::statusChanged, this, &todomain::taskStatusChanged);
        mTasks.append(task);
        // We can do this because task is a QWidget
        ui->tasksLayout->addWidget(task);
        updateStatus();
    }
}

void todomain::removeTask(Task *task)
{
    mTasks.removeOne(task);
    ui->tasksLayout->removeWidget(task);
    /* Ownership transfer does not completely release the task
     * class ownership. What happens is that the task class's parent
     * becomes centralWidget, tasksLayout class's parent, but we don't
     * want that, we want to forget everything about this task, so
     * we explicitly set its parent to null and delete it here.
     */
    task->setParent(0);
    delete task;
    updateStatus();
}

void todomain::taskStatusChanged(Task *task)
{
    updateStatus();
}

void todomain::updateStatus()
{
    int completedCount = 0;
    /* Using C++11 auto var feature here in for-loop to assign the
     * type and var name at each iteration of an iterable container.
     */
    for (auto t : mTasks) {
        if (t->isCompleted()) {
            completedCount++;
        }
    }
    int todoCount = mTasks.size() - completedCount;

    ui->statusLabel->setText(
                QString("Status: %1 todo / %2 completed")
                        .arg(todoCount)
                        .arg(completedCount));
}
