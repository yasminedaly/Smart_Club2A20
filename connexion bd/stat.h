#ifndef STAT_H
#define STAT_H
#include <QDialog>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

#include "commande.h"

#include <QDialog>

namespace Ui {
class stat;
}

class stat : public QDialog
{
    Q_OBJECT

public:
    explicit stat(QWidget *parent = nullptr);
    ~stat();

private:
    Ui::stat *ui;
    commande tmpcm ;
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // STAT_H
