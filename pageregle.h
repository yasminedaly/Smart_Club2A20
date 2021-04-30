#ifndef PAGEREGLE_H
#define PAGEREGLE_H

#include <QDialog>
#include <mainmenu.h>

namespace Ui {
class pageRegle;
}

class pageRegle : public QDialog
{
    Q_OBJECT

public:
    explicit pageRegle(QWidget *parent = 0);
    ~pageRegle();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::pageRegle *ui;
};

#endif // PAGEREGLE_H
