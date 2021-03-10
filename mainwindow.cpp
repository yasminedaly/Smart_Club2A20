#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "etudiant.h"
//#include <QString>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Etmp.afficher());

}


MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pb_ajouter_clicked()
{

    int id=ui->le_id->text().toInt();

     QString nom=ui->le_nom->text();

     QString prenom=ui->le_prenom->text();

    Etudiant E(id,nom,prenom) ;

    bool test=E.ajouter();

    if (test)

    {
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    }



void MainWindow::on_pushButton_clicked()
{
    int id=ui->le_id->text().toInt();
    bool test=Etmp.supprimer(id);

    if (test)

    {
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("suppression effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("suppression non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);




    }



