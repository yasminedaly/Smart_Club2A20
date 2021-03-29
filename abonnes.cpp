#include "abonnes.h"
#include "seances.h"
#include "ui_abonnes.h"
#include "sub.h"
#include <QMessageBox>
#include <QDebug>
#include <QIntValidator>
#include <QPixmap>


Abonnes::Abonnes(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Abonnes)
{

    ui->setupUi(this);
  ui->le_cin->setValidator(new QIntValidator(0, 99999999, this));
  ui->le_num->setValidator(new QIntValidator(0, 99999999, this));
  ui->show_abonnes->setModel(S.afficher());
   ui->show_seances->setModel(A.afficher_S());
   QPixmap pix("C:/Users/21650/Desktop/H/9raya/QT/profil_pic.JPG");
   ui->Profil_pic->setPixmap(pix);

 }


Abonnes::~Abonnes()
{
    delete ui;
}

//add sub
void Abonnes::on_pb_Abonne_clicked()
{
    int Cin=ui->le_cin->text().toInt();
    int Num_tel=ui->le_num->text().toInt();
    QString Nom=ui->le_nom->text();
    QString Prenom=ui->le_prenom->text();
    QString Email=ui->le_email->text();
    QDate ddn_abonnes=ui->le_ddn->date();
    QString type_abonnement=ui->le_type->text();

sub S (Cin,Email,Nom,Prenom,Num_tel,ddn_abonnes,type_abonnement);

bool test=S.ajouter();
        if(test)
            {
            QMessageBox::information(nullptr,QObject::tr("Ok"),
                                 QObject::tr("Ajout effectué\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
                ui->show_abonnes->setModel(S.afficher());
            }
        else
            {
            QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("Ajout non effectué\n"
                                               "Click cancel to exit."),QMessageBox::Cancel);
            }
        }


void Abonnes::on_pb_Seance_clicked()
{
    int ID_salle=ui->le_ID_S->text().toInt();
    int ID_employe=ui->le_ID_E->text().toInt();
    int Num_salle=ui->le_num_s->text().toInt();
    int Capacite_salle=ui->le_capacite->text().toInt();
    QString Titre_cours=ui->le_titre->text();
    QDate Date_seance=ui->le_date->date();
    QString Niveau_seance=ui->le_niv_s->text();
    seances A (ID_salle,ID_employe,Num_salle,Capacite_salle,Titre_cours,Date_seance,Niveau_seance);
    bool test=A.ajouter_S();
            if(test)
                {
                QMessageBox::information(nullptr,QObject::tr("Ok"),
                                     QObject::tr("Ajout effectué\n"
                                                   "Click cancel to exit."),QMessageBox::Cancel);
              ui->show_seances->setModel(A.afficher_S());
                }
            else
                {
                QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                     QObject::tr("Ajout non effectué\n"
                                                   "Click cancel to exit."),QMessageBox::Cancel);
                }
}

void Abonnes::on_supprimer_Abonnes_clicked()
{
    sub S1; S1.setCin(ui->li_delete->text().toInt());
     bool test=S1.supprimer(S1.getCin());
   if (test)
   {

       QMessageBox::information(nullptr,QObject::tr("Ok"),
                            QObject::tr("suppression effectué\n"
                                          "Click cancel to exit."),QMessageBox::Cancel);
       ui->show_abonnes->setModel(S.afficher());

       }
   else
       {
       QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                            QObject::tr("suppression non effectué\n"
                                          "Click cancel to exit."),QMessageBox::Cancel);
       }
   }


void Abonnes::on_modifier_Abonnes_clicked()
    {       int Cin=ui->li_cin->text().toInt();
            int Num_tel=ui->li_tel->text().toInt();
            QString Nom=ui->li_nom->text();
            QString Prenom=ui->li_prenom->text();
            QString Email=ui->li_email->text();
            QDate ddn_abonnes=ui->li_date_s->date();
           QString type_abonnement=ui->li_ab->text();



        sub S (Cin,Email,Nom,Prenom,Num_tel,ddn_abonnes,type_abonnement);

            bool test=S.modifier();
            if(test)

                {
                QMessageBox::information(nullptr,QObject::tr("Ok"),
                                     QObject::tr("Modification effectuée\n"
                                                   "Click cancel to exit."),QMessageBox::Cancel);
                ui->show_abonnes->setModel(S.afficher());
                }
            else
                {
                QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                     QObject::tr("Modification non effectuée\n"
                                                   "Click cancel to exit."),QMessageBox::Cancel);
                }
            }





void Abonnes::on_modifier_seances_clicked()
{

    int ID_salle=ui->li_id->text().toInt();
    int Num_salle=ui->li_salle->text().toInt();
    int ID_employe=ui->li_id_e->text().toInt();
    int Capacite_salle=ui->li_cap->text().toInt();
    QString Titre_cours=ui->li_titre->text();
    QDate Date_seance=ui->li_date->date();
    QString Niveau_seance=ui->li_cour->text();


     seances A (ID_salle,Num_salle,ID_employe,Capacite_salle,Titre_cours,Date_seance,Niveau_seance);

            bool test=A.modifier_S();
            if(test)

                {
                QMessageBox::information(nullptr,QObject::tr("Ok"),
                                     QObject::tr("Modification effectuée\n"
                                                   "Click cancel to exit."),QMessageBox::Cancel);
                    ui->show_seances->setModel(A.afficher_S());
                }
            else
                {
                QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                     QObject::tr("Modification non effectuée\n"
                                                   "Click cancel to exit."),QMessageBox::Cancel);
                }

}

void Abonnes::on_supprimer_seances_clicked()
{
    seances A1; A1.setID_salle(ui->li_delete_S->text().toInt());
     bool test=A1.supprimer_S(A1.getID_salle());
   if (test)
   {

       QMessageBox::information(nullptr,QObject::tr("Ok"),
                            QObject::tr("suppression effectué\n"
                                          "Click cancel to exit."),QMessageBox::Cancel);
       ui->show_seances->setModel(A.afficher_S());

       }
   else
       {
       QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                            QObject::tr("suppression non effectué\n"
                                          "Click cancel to exit."),QMessageBox::Cancel);
       }
}
