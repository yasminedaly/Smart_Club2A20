#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "fournisseurs.h"
#include "factures.h"

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

    void on_pushButton_ajouterfacture_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_ajouterfournisseur_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;
    Fournisseurs Fotmp;
    Factures Fatmp ;
};
#endif // MAINWINDOW_H
