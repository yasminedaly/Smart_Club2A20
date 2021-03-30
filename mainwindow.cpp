#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "joueur.h"
#include "partie.h"
#include <QMessageBox>
#include <QDebug>
#include <QDate>
#include <QString>
#include <QIntValidator>
#include <QSqlQuery>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->id_j->setValidator (new QIntValidator(0, 9999, this));
    ui->tel_j->setValidator (new QIntValidator(100000000, 99999999, this));
    ui->classement_j->setValidator (new QIntValidator(0, 9999, this));
    ui->tab_afficher_joueur->setModel(J.afficher_joueur());
    ui->tab_afficher_partie->setModel(P.afficher_partie());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_joueur_clicked()
{
    int id_joueur=ui->id_j->text().toInt();
    QString nom_joueur=ui->nom_j->text();
    QString prenom_joueur=ui->prenom_j->text();
    QString ville_joueur=ui->ville_j->text();
    QDate date= ui->dn_j->date();
    QString dn_joueur= date.toString("dd/MM/yy");
    QString email_joueur=ui->email_j->text();
    int tel_joueur=ui->tel_j->text().toInt();
    int classement_elo=ui->classement_j->text().toInt();

    Joueur J(id_joueur,nom_joueur,prenom_joueur,ville_joueur,dn_joueur,email_joueur,tel_joueur,classement_elo);

    if( J.verifint(J.getid_joueur())==true && J.verifvidestring(J.getnom_joueur())==true && J.verifvidestring(J.getprenom_joueur())==true &&
            J.verifvidestring(J.getville_joueur())==true && J.verifvidestring(J.getdn_joueur())==true && J.verifvidestring(J.getemail_joueur())==true &&
            J.verifint(J.gettel_joueur())==true && J.verifint(J.getclassement_elo())==true)
       {
        bool test=J.ajouter_joueur();
        if(test)

            {
            QMessageBox::information(nullptr,QObject::tr("Ok"),
                                 QObject::tr("Ajout effectué\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
            ui->tab_afficher_joueur->setModel(J.afficher_joueur());
            }
        else
            {
            QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("Ajout non effectué\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
            }
        }
}

void MainWindow::on_supprimer_joueur_clicked()
{

    Joueur J1;
    J1.setid_joueur(ui->id_j_supp->text().toInt());
    bool test = J1.verifierid(J1.getid_joueur());
    if(test)
    {
        J1.supprimer_joueur(J1.getid_joueur());
        QMessageBox::information(nullptr,QObject::tr("Ok"),
                                 QObject::tr("Suppression effectué\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
        ui->tab_afficher_joueur->setModel(J.afficher_joueur());
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("Suppression non effectué\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
    }
}




void MainWindow::on_modifier_joueur_clicked()
{


    int id_joueur=ui->id_j->text().toInt();
    QString nom_joueur=ui->nom_j->text();
    QString prenom_joueur=ui->prenom_j->text();
    QString ville_joueur=ui->ville_j->text();
    QDate date= ui->dn_j->date();
    QString dn_joueur= date.toString("dd/MM/yy");
    QString email_joueur=ui->email_j->text();
    int tel_joueur=ui->tel_j->text().toInt();
    int classement_elo=ui->classement_j->text().toInt();

    Joueur J(id_joueur,nom_joueur,prenom_joueur,ville_joueur,dn_joueur,email_joueur,tel_joueur,classement_elo);

    if( J.verifint(J.getid_joueur())==true && J.verifvidestring(J.getnom_joueur())==true && J.verifvidestring(J.getprenom_joueur())==true &&
            J.verifvidestring(J.getville_joueur())==true && J.verifvidestring(J.getdn_joueur())==true && J.verifvidestring(J.getemail_joueur())==true &&
            J.verifint(J.gettel_joueur())==true && J.verifint(J.getclassement_elo())==true)
       {
        bool test=J.modifier_joueur();
        if(test)

            {
            QMessageBox::information(nullptr,QObject::tr("Ok"),
                                 QObject::tr("Modification effectuée\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
            ui->tab_afficher_joueur->setModel(J.afficher_joueur());
            }
        else
            {
            QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("Modification non effectuée\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
            }
        }

}

void MainWindow::on_ajouter_partie_clicked()
{
    int id_partie=ui->id_p->text().toInt();
    QString cadence=ui->cadence->text();
    int id_noir=ui->id_n->text().toInt();
    int id_blanc=ui->id_b->text().toInt();
    QDateTime date1=ui->debut_p->dateTime();
    QString debut_partie= date1.toString("dd/MM/yy");
    QDateTime date2=ui->fin_p->dateTime();
    QString fin_partie= date2.toString("dd/MM/yy");
    QString gagnant_partie=ui->gagnant_p->text();
    int num_table=ui->table_p->text().toInt();
    QString com_partie=ui->com_p->text();

    Partie P(id_partie,cadence,id_noir,id_blanc,debut_partie,fin_partie,gagnant_partie,num_table,com_partie);

    if( P.verifint(P.getid_partie())==true && P.verifvidestring(P.getcadence())==true && P.verifint(P.getid_noir())==true &&
            P.verifint(P.getid_blanc())==true && P.verifvidestring(P.getdebut_partie())==true && P.verifvidestring(P.getfin_partie())==true &&
            P.verifvidestring(P.getgagnant_partie())==true && P.verifint(P.getnum_table())==true && P.verifvidestring(P.getcom_partie())==true )
       {
        bool test=P.ajouter_partie();
        if(test)

            {
            QMessageBox::information(nullptr,QObject::tr("Ok"),
                                 QObject::tr("Ajout effectué\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
            ui->tab_afficher_partie->setModel(P.afficher_partie());
            }
        else
            {
            QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("Ajout non effectué\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
            }
        }
}



void MainWindow::on_supprimer_partie_clicked()
{
    Partie P;
    P.setid_partie(ui->id_p_supp->text().toInt());
    bool test = P.verifierid(P.getid_partie());
    if(test)
    {
        P.supprimer_partie(P.getid_partie());
        QMessageBox::information(nullptr,QObject::tr("Ok"),
                                 QObject::tr("Suppression effectué\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
        ui->tab_afficher_partie->setModel(P.afficher_partie());
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("Suppression non effectué\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_modifier_partie_clicked()
{
    int id_partie=ui->id_p->text().toInt();
    QString cadence=ui->cadence->text();
    int id_noir=ui->id_n->text().toInt();
    int id_blanc=ui->id_b->text().toInt();
    QDateTime date1=ui->debut_p->dateTime();
    QString debut_partie= date1.toString("dd/MM/yy");
    QDateTime date2=ui->fin_p->dateTime();
    QString fin_partie= date2.toString("dd/MM/yy");
    QString gagnant_partie=ui->gagnant_p->text();
    int num_table=ui->table_p->text().toInt();
    QString com_partie=ui->com_p->text();

    Partie P(id_partie,cadence,id_noir,id_blanc,debut_partie,fin_partie,gagnant_partie,num_table,com_partie);

    if( P.verifint(P.getid_partie())==true && P.verifvidestring(P.getcadence())==true && P.verifint(P.getid_noir())==true &&
            P.verifint(P.getid_blanc())==true && P.verifvidestring(P.getdebut_partie())==true && P.verifvidestring(P.getfin_partie())==true &&
            P.verifvidestring(P.getgagnant_partie())==true && P.verifint(P.getnum_table())==true && P.verifvidestring(P.getcom_partie())==true )
       {
        bool test=P.modifier_partie();
        if(test)

            {
            QMessageBox::information(nullptr,QObject::tr("Ok"),
                                 QObject::tr("Modification effectuée\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
            ui->tab_afficher_partie->setModel(P.afficher_partie());
            }
        else
            {
            QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("Modification non effectuée\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
            }
        }
}
