#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "fournisseurs.h"
#include "factures.h"
#include "produits.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_ajouter_fournisseur__clicked();

    void on_supprimer_fournisseur__clicked();

    void on_modifier_fournisseur__clicked();

    void on_pushButton_ajouterfacture_clicked();

    void on_pushButton_2_clicked();

    void on_supprimer_facture_clicked();

    void on_pushButton_29_clicked();

    void on_modifier_facture_clicked();

    void on_supprimer_facture_2_clicked();

    void on_lineEdit_6();
    void on_pushButton_11_clicked()




private:
    Ui::MainWindow *ui;

    Fournisseurs Fotmp;
    Factures Fatmp ;
    Produits Ptmp ;

};
#endif
