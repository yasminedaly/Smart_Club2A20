#ifndef ABONNES_H
#define ABONNES_H
#include <QString>
#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "sub.h"
#include "seances.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Abonnes; }
QT_END_NAMESPACE

class Abonnes : public QMainWindow
{

    Q_OBJECT

public:
    Abonnes(QWidget *parent = nullptr);
    
    ~Abonnes();

private slots:


    void on_pb_Abonne_clicked();

    void on_supprimer_Abonnes_clicked();

    void on_pb_Seance_clicked();


    void on_modifier_Abonnes_clicked();

    void on_modifier_seances_clicked();

    void on_supprimer_seances_clicked();

private:
    Ui::Abonnes *ui;
    sub S;
    sub tmpsub;
    int Cin=211;
    seances A;
};
#endif // ABONNES_H
