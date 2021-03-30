#include "joueur.h"
#include <QSqlQuery>
#include <QDebug>
#include<QDate>
#include <QObject>

Joueur::Joueur()
{
id_joueur=0;
}
Joueur::Joueur(int id_joueur,QString nom_joueur, QString prenom_joueur,QString ville_joueur, QString dn_joueur,QString email_joueur, int tel_joueur, int classement_elo)
{
    this->id_joueur=id_joueur;
    this->nom_joueur=nom_joueur;
    this->prenom_joueur=prenom_joueur;
    this->ville_joueur=ville_joueur;
    this->dn_joueur=dn_joueur;
    this->email_joueur=email_joueur;
    this->tel_joueur=tel_joueur;
    this->classement_elo=classement_elo;
}
int Joueur::getid_joueur(){return id_joueur;}
QString Joueur::getnom_joueur(){return nom_joueur;}
QString Joueur::getprenom_joueur(){return prenom_joueur;}
QString Joueur::getville_joueur(){return ville_joueur;}
QString Joueur::getdn_joueur(){return dn_joueur;}
QString Joueur::getemail_joueur(){return email_joueur;}
int Joueur::gettel_joueur(){return tel_joueur;}
int Joueur::getclassement_elo(){return classement_elo;}

void Joueur::setid_joueur(int id_joueur){this->id_joueur=id_joueur;}
void Joueur::setnom_joueur(QString nom_joueur){this->nom_joueur=nom_joueur;}
void Joueur::setprenom_joueur(QString prenom_joueur){this->prenom_joueur=prenom_joueur;}
void Joueur::setville_joueur(QString ville_joueur){this->ville_joueur=ville_joueur;}
void Joueur::setdn_joueur(QString dn_joueur){this->dn_joueur=dn_joueur;}
void Joueur::setemail_joueur(QString email_joueur){this->email_joueur=email_joueur;}
void Joueur::settel_joueur(int tel_joueur){this->tel_joueur=tel_joueur;}
void Joueur::setclassement_elo(int classement_elo){this->classement_elo=classement_elo;}
bool Joueur::ajouter_joueur()
{
    bool test=false;


    QSqlQuery query;
    QString id_string=QString::number(id_joueur);
    QString tel_string=QString::number(tel_joueur);
    QString classement_string=QString::number(classement_elo);
    QDate dn_date =QDate::fromString(dn_joueur,"dd/MM/yy");
    query.prepare("INSERT INTO joueurs (id_joueur,nom_joueur,prenom_joueur,ville_joueur,dn_joueur, email_joueur,tel_joueur, classement_elo) "
                  "VALUES (:id_joueur, :nom_joueur, :prenom_joueur, :ville_joueur, :dn_joueur, :email_joueur, :tel_joueur, :classement_elo)");
    query.bindValue(0, id_string);
    query.bindValue(1, nom_joueur);
    query.bindValue(2, prenom_joueur);
    query.bindValue(3, ville_joueur);
    query.bindValue(4, dn_date);
    query.bindValue(5,email_joueur);
    query.bindValue(6,tel_string);
    query.bindValue(7,classement_string);
    return query.exec();


    return test;
}

bool Joueur::verifierid(int id_joueur)
{  QSqlQuery  query;
    bool test=false;
      QString id_string=QString::number(id_joueur);
        query.prepare("SELECT * from joueurs where id_joueur=:id_joueur");
         query.bindValue(":id_joueur",id_string);
    if(query.exec()&&query.next())
    {     test=true;
         return test;
    }
    return test;
}

bool Joueur::verifvidestring(QString S)
{
    bool test=true;
        if(S.length()==0)
         {  test=false;
            return test;}
        return test;
}

bool Joueur ::verifint(int S)
{
    bool test=true;
        if(S==0)
         {  test=false;
            return test;}
        return test;

}

bool Joueur::supprimer_joueur(int id_joueur)
{
    QSqlQuery query;
    QString id_string=QString::number(id_joueur);
    query.prepare("DELETE from joueurs where id_joueur=:id_joueur");
    query.bindValue(":id_joueur", id_string);
    return query.exec();



}


QSqlQueryModel * Joueur::afficher_joueur()
{
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery("SELECT * FROM joueurs");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Ville"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Classement élo"));

    return model;
}

bool Joueur ::modifier_joueur()
{
    QSqlQuery query;
    QString id_string=QString::number(id_joueur);
    QString tel_string=QString::number(tel_joueur);
    QString classement_string=QString::number(classement_elo);
    QDate dn_date =QDate::fromString(dn_joueur,"dd/MM/yy");

   query.prepare("UPDATE joueurs set nom_joueur=:nom_joueur,prenom_joueur=:prenom_joueur,ville_joueur=:ville_joueur,dn_joueur=:dn_joueur,email_joueur=:email_joueur,tel_joueur=:tel_joueur,classement_elo=:classement_elo WHERE id_joueur=:id_joueur");
   query.bindValue(":id_joueur",id_string);
   query.bindValue(":nom_joueur",nom_joueur);
   query.bindValue(":prenom_joueur",prenom_joueur);
   query.bindValue(":ville_joueur",ville_joueur);
   query.bindValue(":dn_joueur",dn_date);
   query.bindValue(":email_joueur",email_joueur);
   query.bindValue(":tel_joueur",tel_string);
   query.bindValue(":classement_elo",classement_string);
   return query.exec();

}
