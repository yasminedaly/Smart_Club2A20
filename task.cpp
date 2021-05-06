#include "task.h"
#include "ui_task.h"
#include <QInputDialog>
#include <QFont>

Task::Task(const QString &name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);
    setName(name);
    connect(ui->editButton, &QPushButton::clicked,
            this, &Task::rename);

    // Using a C++11 lambda here to connect the clicked
    // signal to an anon inline function. Qt 5 accepts
    // a lambda instead of a slot in a connect call if you want.
    // 'emit' is a Qt macro that immediately triggers the connected
    // slot with what we passed in as a parameter, here a Task.
    connect(ui->removeButton, &QPushButton::clicked,
            [this] {
                    emit removed(this);
                   });
    /* C++11 lambdas defined:
     * syntax:
     * [ capture-list ] (params) -> ret { body };
     * capture-list: defines what vars visible in the lambda scope.
     * params: fn param type list can be passed to lambda scope. You
     * can leave out () if there are none if you want, like above.
     * ret: return type. Can be ommited if there is none, like above.
     * body: code with access to capture-list and params and must
     * return a var with type 'ret'.
     */
    connect(ui->checkbox, &QCheckBox::toggled, this, &Task::checked);
}

Task::~Task()
{
    delete ui;
}

/* Set name on UI 'checkbox' named element
 * to string given
 */
void Task::setName(const QString &name)
{
    ui->checkbox->setText(name);
}

QString Task::name() const
{
    return ui->checkbox->text();
}
// Return whether or not 'checkbox' UI element is checked
bool Task::isCompleted() const
{
    return ui->checkbox->isChecked();
}

void Task::rename()
{
    bool ok;
    QString value = QInputDialog::getText(this, tr("Edit task"),
                                          tr("Task name"),
                                          QLineEdit::Normal,
                                          this->name(), &ok);
    if (ok && !value.isEmpty()) {
        setName(value);
    }
}

void Task::checked(bool checked)
{
    // Create copy of current font styel
    QFont font(ui->checkbox->font());
    // Strike it out
    font.setStrikeOut(checked);
    // Set it
    ui->checkbox->setFont(font);
    // Emit signal
    emit statusChanged(this);
}
