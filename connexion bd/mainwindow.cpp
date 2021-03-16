#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "commande.h"
#include "bibliotheques.h"
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QPushButton>
#include <QPrinter>
#include <QPdfWriter>
#include <QApplication>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
#include <QTextBrowser>
#include <QFileDialog>
#include <QtTextToSpeech>
#include <QTextBlock>
#include <QTextEdit>
#include <cstdlib>
#include <QRadioButton>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix ("C:/Users/khaled/Desktop/QT test/qt+oracle/connexion bd/gestion commande/connexion bd/back.jpg");
    QPixmap pix2 ("C:/Users/khaled/Desktop/QT test/qt+oracle/connexion bd/gestion commande/connexion bd/back.jpg");


    ui->back->setPixmap(pix);
   // ui->pb_ajouter->setBackgroundRole(pix2);
    ui->tableView_2->setModel(Etmp.afficher());
    ui->tableView_bib->setModel(Etmpb.afficher_livre());


}


MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pb_ajouter_clicked()
{

    int id_commande=ui->le_id->text().toInt();

    int nb_produit=ui->le_nb->text().toInt();

    float Prix_t=ui->le_prix->text().toFloat();

     QString Date_commande=ui->dateEdit->date().toString("dd / MM / yyyy ");
    // QString dateabs= ui->date->date().toString("dd / MM / yyyy ");



    commande c(id_commande,nb_produit,Prix_t,Date_commande) ;

    bool test=c.ajouter();

    if (test)

    {
        ui->tableView_2->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    }






void MainWindow::on_pushButton_sup_clicked()

{
    int id_commande=ui->le_id->text().toInt();
    bool test=Etmp.supprimer(id_commande);

    if (test)

    {
        ui->tableView_2->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("suppression effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("suppression non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);




}

void MainWindow::on_pushButton_mod_clicked()
{
    int id_commande=ui->le_id->text().toInt();

    int nb_produit=ui->le_nb->text().toInt();

    float Prix_t=ui->le_prix->text().toFloat();

     QString Date_commande=ui->dateEdit->text();

       commande c(id_commande,nb_produit,Prix_t,Date_commande) ;

       bool test=c.modifier(id_commande, nb_produit, Prix_t,Date_commande) ;

       if (test)

       {
           ui->tableView_2->setModel(Etmp.afficher());
           QMessageBox::information(nullptr, QObject::tr("ok"),
                       QObject::tr("modification effectué.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

   }
       else
           QMessageBox::critical(nullptr, QObject::tr("not ok"),
                       QObject::tr("modification non effectué.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);




}

void MainWindow::on_pushButton_rch_clicked()
{

    int id_commandeAA=ui->rch_2->text().toInt();

        QSqlQueryModel * model= new QSqlQueryModel();
        QSqlQuery* qeury=new QSqlQuery();
        qeury->prepare("SELECT * from commande where id_commande=:id_commandeAA");
        qeury->bindValue(":id_commandeAA",id_commandeAA);



        qeury->exec();
        if(qeury->next())
        {
            erreur->setMedia(QUrl("C:/Users/khaled/Desktop/QT test/qt+oracle/connexion bd/sounds/compteexiste.mp3")) ;
                erreur->setVolume(100) ;
                erreur->play() ;
                model->setQuery(*qeury);
                ui->tableView_2->setModel(model) ;
                ui->tableView_2->setModel(Etmp.afficher());//refresh


        }
        else
        {
            erreur->setMedia(QUrl("C:/Users/khaled/Desktop/QT test/qt+oracle/connexion bd/sounds/comptenot.mp3")) ;
                erreur->setVolume(100) ;
                erreur->play() ;
        }

}

void MainWindow::on_Liv_ajouter_clicked()

    {





    int id_l=ui->id_Liv->text().toInt();
    QString nom_l=ui->nom_liv->text() ;
    QString Ref_livre=ui->ref_liv->text() ;
    QString desc_l=ui->desc_liv->toPlainText() ;
    QString date_s=ui->dateS_liv->date().toString("dd / MM / yyyy ") ;
    QString date_r=ui->dateR_liv->date().toString("dd / MM / yyyy ") ;
    QString displ=ui->oui_liv->text()  ;
   // QString displ1=ui->non_liv_2->text()  ;



    if (ui->oui_liv->isChecked())

    {
    QString displ=ui->oui_liv->text() ;

       }

     QString displ1=ui->non_liv_2->text() ;

      if (ui->non_liv_2->isChecked())
      {
         QString displ1=ui->non_liv_2->text() ;
       }


    Bibliotheques B(id_l,nom_l,Ref_livre,desc_l,date_s,date_r,displ,displ1) ;

    bool test=B.ajouter_livre();



    if (test)

    {
        ui->tableView_bib->setModel(Etmpb.afficher_livre());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



}

void MainWindow::on_liv_supprimer_clicked()
{

    int id_l=ui->id_Liv->text().toInt();
    bool test=Etmpb.supprimer_livre(id_l);

    if (test)

    {
        ui->tableView_bib->setModel(Etmpb.afficher_livre());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("suppression effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("suppression non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_Liv_modifier_clicked()
{


    int id_l=ui->id_Liv->text().toInt();
    QString nom_l=ui->nom_liv->text() ;
    QString Ref_livre=ui->ref_liv->text() ;
    QString desc_l=ui->desc_liv->toPlainText() ;
    QString date_s=ui->dateS_liv->date().toString("dd / MM / yyyy ") ;
    QString date_r=ui->dateR_liv->date().toString("dd / MM / yyyy ") ;
    QString displ=ui->oui_liv->text()  ;
    QString displ1=ui->non_liv_2->text() ;


    Bibliotheques B(id_l,nom_l,Ref_livre,desc_l,date_s,date_r,displ,displ1) ;

       bool test=B.modifier_livre(id_l,nom_l,Ref_livre,desc_l,date_s,date_r,displ,displ1) ;

       if (test)

       {
           ui->tableView_bib->setModel(Etmpb.afficher_livre());
           QMessageBox::information(nullptr, QObject::tr("ok"),
                       QObject::tr("modification effectué.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

   }
       else
           QMessageBox::critical(nullptr, QObject::tr("not ok"),
                       QObject::tr("modification non effectué.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);



}





void MainWindow::on_pushButton_rch_livre_clicked()
{


    int id_lAA=ui->rch_livre->text().toInt();

        QSqlQueryModel * model= new QSqlQueryModel();
        QSqlQuery* qeury=new QSqlQuery();
        qeury->prepare("SELECT * from BIBLIOTHEQUE where id_l=:id_lAA");
        qeury->bindValue(":id_lAA",id_lAA);



        qeury->exec();
        if(qeury->next())
        {
            erreur->setMedia(QUrl("C:/Users/khaled/Desktop/QT test/qt+oracle/connexion bd/sounds/compteexiste.mp3")) ;
                erreur->setVolume(100) ;
                erreur->play() ;
                model->setQuery(*qeury);
                ui->tableView_bib->setModel(model) ;
                ui->tableView_bib->setModel(Etmpb.afficher_livre());

        }
        else
        {
            erreur->setMedia(QUrl("C:/Users/khaled/Desktop/QT test/qt+oracle/connexion bd/sounds/comptenot.mp3")) ;
                erreur->setVolume(100) ;
                erreur->play() ;
        }
}

void MainWindow::on_tri_commande_clicked()

    {
    ui->tableView_2->setModel(Etmp.tri());
      ui->tableView_2->setModel(Etmp.tri());//refresh

    }

void MainWindow::on_pushButton_tri_livre_clicked()

    {
    ui->tableView_bib->setModel(Etmpb.tri_livre());
      ui->tableView_bib->setModel(Etmpb.tri_livre());

    }
