#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "evenement.h"
#include <QSqlQuery>
#include <QIntValidator>
#include "ticket.h"
#include <QString>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
    ui->le_id->setValidator (new QIntValidator(0, 9999, this));
       ui->le_num->setValidator (new QIntValidator(100000000, 99999999, this));
       ui->le_nb->setValidator (new QIntValidator(0, 9999, this));
      */
    ui->tableView->setModel(Etmp.afficher());
     ui->tableView_2->setModel(Etmpp.afficher());

}


MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_ajouter_2_clicked()
{

    int id=ui->le_id->text().toInt();

     QString nom=ui->le_nom->text();

     QString adresse=ui->le_adresse->text();
     int num=ui->le_num->text().toInt();
     int nb=ui->le_nb->text().toInt();
     QString date=ui->le_date->text();

   Evenement E(id,nom,adresse,num,nb,date) ;

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



void MainWindow::on_supp_event_clicked()
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

void MainWindow::on_ajouter_3_clicked()
{
   // Evenement E;
    int id=ui->le_id->text().toInt();

     QString nom=ui->le_nom->text();

     QString adresse=ui->le_adresse->text();
     int num=ui->le_num->text().toInt();
     int nb=ui->le_nb->text().toInt();
     QString date=ui->le_date->text();

   Evenement E (id,nom,adresse,num,nb,date) ;

    bool test=E.modifier(id,nom,adresse,num,nb,date);
    if (test)

    {
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("Modification effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("Modification non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



}

void MainWindow::on_rechercher_clicked()
{
    //click->play();


            QString text;

            text=ui->le_nom_2->text();

            if(text == "")

            {

                ui->tableView->setModel(Etmp.afficher());

            }

            else

            {



                ui->tableView->setModel(Etmp.recherche(text));

            }
}
void MainWindow::on_trie_clicked()
{

    ui->tableView->setModel(Etmp.afficher_trie());
}
// ticket

void MainWindow::on_ajouter_clicked()
{

    int id_ticket=ui->le_id_2->text().toInt();

    int id_evenement=ui->le_id_4->text().toInt();

     QString type_acheteur=ui->le_type_1->text();
     QString type=ui->le_type_2->text();
     int prix=ui->le_prix->text().toInt();
     QString date_achat=ui->le_date_2->text();
   Ticket T(id_ticket,id_evenement,type_acheteur,type,prix,date_achat) ;
   //Ticket T(id_ticket,id_evenement,type_acheteur,type_ticket,prix,date_achat) ;

    bool test=T.ajouter();

    if (test)

    {
        ui->tableView_2->setModel(Etmpp.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_supp_clicked()
{
    int id_ticket=ui->le_id_2->text().toInt();
    bool test=Etmpp.supprimer(id_ticket);

    if (test)

    {
        ui->tableView_2->setModel(Etmpp.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("suppression effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("suppression non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}


void MainWindow::on_recherche_Ticket_clicked()
{
            QString text;

            text=ui->le_type_3->text();

            if(text == "")

            {

                ui->tableView_2->setModel(Etmpp.afficher());
            }

            else

            {



                ui->tableView_2->setModel(Etmpp.recherche(text));

            }
}


