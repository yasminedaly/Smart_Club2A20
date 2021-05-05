#ifndef CHOIXUPGRADE_H
#define CHOIXUPGRADE_H

#include <QDialog>

namespace Ui {
class ChoixUpgrade;
}

class ChoixUpgrade : public QDialog
{
    Q_OBJECT

public:
    explicit ChoixUpgrade(QWidget *parent = 0);
    ~ChoixUpgrade();

private slots:
    void on_btn_reine_clicked();

    void on_btn_tour_clicked();

    void on_btn_fou_clicked();
    void on_btn_cavalier_clicked();

signals:
    void btn_reine_clicked();
    void btn_tour_clicked();
    void btn_fou_clicked();
    void btn_cavalier_clicked();
private:
    Ui::ChoixUpgrade *ui;
};

#endif // CHOIXUPGRADE_H
