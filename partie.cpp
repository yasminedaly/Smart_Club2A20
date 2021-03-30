#include "partie.h"
#include <QSqlQuery>
#include <QDebug>
#include<QDate>
#include <QObject>

Partie::Partie()
{
id_partie=0;
}
Partie::Partie(int id_partie,QString cadence,int id_noir,int id_blanc,QString debut_partie,QString fin_partie,QString gagnant_partie,int num_table,QString com_partie)
{
    this->id_partie=id_partie;
    this->cadence=cadence;
    this->id_noir=id_noir;
    this->id_blanc=id_blanc;
    this->debut_partie=debut_partie;
    this->fin_partie=fin_partie;
    this->gagnant_partie=gagnant_partie;
    this->num_table=num_table;
    this->com_partie=com_partie;


}

int Partie::getid_partie(){return id_partie;}
QString Partie:: getcadence(){return cadence;}
int Partie:: getid_noir(){return id_noir;}
int Partie:: getid_blanc(){return id_blanc;}
QString Partie:: getdebut_partie(){return debut_partie;}
QString Partie:: getfin_partie(){return fin_partie;}
QString Partie:: getgagnant_partie(){return gagnant_partie;}
int Partie:: getnum_table(){return num_table;}
QString Partie:: getcom_partie(){return com_partie;}

void Partie::setid_partie(int id_partie){this->id_partie=id_partie;}
void Partie::setcadence(QString cadence){this->cadence=cadence;}
void Partie::setid_noir(int id_noir){this->id_noir=id_noir;}
void Partie::setid_blanc(int id_blanc){this->id_blanc=id_blanc;}
void Partie::setdebut_partie(QString debut_partie){this->debut_partie=debut_partie;}
void Partie::setfin_partie(QString fin_partie){this->fin_partie=fin_partie;}
void Partie::setgagnant_partie(QString gagnant_partie){this->gagnant_partie=gagnant_partie;}
void Partie::setnum_table(int num_table){this->num_table=num_table;}
void Partie::setcom_partie(QString com_partie){this->com_partie=com_partie;}

bool Partie::ajouter_partie()
{
    bool test=false;


    QSqlQuery query;
    QString id_string=QString::number(id_partie);
    QString noir_string=QString::number(id_noir);
    QString blanc_string=QString::number(id_blanc);
    QString table_string=QString::number(num_table);
    QDate debut_date =QDate::fromString(debut_partie,"dd/MM/yy");
    QDate fin_date =QDate::fromString(fin_partie,"dd/MM/yy");
    query.prepare("INSERT INTO parties (id_partie,cadence,id_noir,id_blanc,debut_partie,fin_partie,gagnant_partie,num_table,com_partie) "
                  "VALUES (:id_partie,:cadence,:id_noir,:id_blanc,:debut_partie,:fin_partie,:gagnant_partie,:num_table,:com_partie)");
    query.bindValue(0, id_string);
    query.bindValue(1, cadence);
    query.bindValue(2, noir_string);
    query.bindValue(3, blanc_string);
    query.bindValue(4, debut_date);
    query.bindValue(5,fin_date);
    query.bindValue(6,gagnant_partie);
    query.bindValue(7,table_string);
    query.bindValue(8,com_partie);
    return query.exec();


    return test;
}

bool Partie::verifierid(int id_partie)
{  QSqlQuery  query;
    bool test=false;
      QString id_string=QString::number(id_partie);
        query.prepare("SELECT * from parties where id_partie=:id_partie");
         query.bindValue(":id_partie",id_string);
    if(query.exec()&&query.next())
    {     test=true;
         return test;
    }
    return test;
}

bool Partie::verifvidestring(QString S)
{
    bool test=true;
        if(S.length()==0)
         {  test=false;
            return test;}
        return test;
}
bool Partie ::verifint(int S)
{
    bool test=true;
        if(S==0)
         {  test=false;
            return test;}
        return test;

}

QSqlQueryModel * Partie::afficher_partie()
{
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery("SELECT * FROM parties");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Cadence"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Joueur noir"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Joueur blanc"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Heure de début"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Heure de fin"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Gagnant"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Num table"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Commentaire"));

    return model;
}

bool Partie::supprimer_partie(int id_partie)
{
    QSqlQuery query;
    QString id_string=QString::number(id_partie);
    query.prepare("DELETE from parties where id_partie=:id_partie");
    query.bindValue(":id_partie", id_string);
    return query.exec();



}

bool Partie ::modifier_partie()
{
    QSqlQuery query;
    QString id_string=QString::number(id_partie);
    QString noir_string=QString::number(id_noir);
    QString blanc_string=QString::number(id_blanc);
    QString table_string=QString::number(num_table);
    QDate debut_date =QDate::fromString(debut_partie,"dd/MM/yy");
    QDate fin_date =QDate::fromString(fin_partie,"dd/MM/yy");
    query.prepare("UPDATE parties set cadence=:cadence,id_noir=:id_noir,id_blanc=:id_blanc,debut_partie=:debut_partie,fin_partie=:fin_partie,gagnant_partie=:gagnant_partie,num_table=:num_table,com_partie=:com_partie WHERE id_partie=:id_partie");



   query.bindValue(":id_partie", id_string);
   query.bindValue(":cadence", cadence);
   query.bindValue(":id_noir", noir_string);
   query.bindValue(":id_blanc", blanc_string);
   query.bindValue(":debut_partie", debut_date);
   query.bindValue(":fin_partie",fin_date);
   query.bindValue(":gagnant_partie",gagnant_partie);
   query.bindValue(":num_table",table_string);
   query.bindValue(":com_partie",com_partie);
   return query.exec();
   return query.exec();

}

QSqlQueryModel* Partie::chercher_partie(int index,QString text)
{
QSqlQuery query;
    QSqlQueryModel* model=new QSqlQueryModel();
    if(index==0)
   { query.prepare("SELECT * FROM parties where id_partie like '"+text+"'");
     query.exec();
     model->setQuery(query);
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("Cadence"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("Joueur noir"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("Joueur blanc"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("Heure de début"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("Heure de fin"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("Gagnant"));
     model->setHeaderData(7, Qt::Horizontal, QObject::tr("Num table"));
     model->setHeaderData(8, Qt::Horizontal, QObject::tr("Commentaire"));
     }
   if(index==1)
      {
       query.prepare("SELECT * FROM parties where cadence like '"+text+"'");
           query.exec();
           model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("Cadence"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("Joueur noir"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("Joueur blanc"));
           model->setHeaderData(4, Qt::Horizontal, QObject::tr("Heure de début"));
           model->setHeaderData(5, Qt::Horizontal, QObject::tr("Heure de fin"));
           model->setHeaderData(6, Qt::Horizontal, QObject::tr("Gagnant"));
           model->setHeaderData(7, Qt::Horizontal, QObject::tr("Num table"));
           model->setHeaderData(8, Qt::Horizontal, QObject::tr("Commentaire"));
   }


    return model;

}

QSqlQueryModel* Partie::trier_partie(int index)
{
    QSqlQuery query;
        QSqlQueryModel* model=new QSqlQueryModel();
        if(index==0)
       { query.prepare("SELECT * FROM parties ORDER BY id_partie DESC");
         query.exec();
         model->setQuery(query);
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("Cadence"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("Joueur noir"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("Joueur blanc"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("Heure de début"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("Heure de fin"));
         model->setHeaderData(6, Qt::Horizontal, QObject::tr("Gagnant"));
         model->setHeaderData(7, Qt::Horizontal, QObject::tr("Num table"));
         model->setHeaderData(8, Qt::Horizontal, QObject::tr("Commentaire"));
        }

       if(index==1)
          {
           query.prepare("SELECT * FROM parties ORDER BY num_table DESC");
               query.exec();
               model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
               model->setHeaderData(1, Qt::Horizontal, QObject::tr("Cadence"));
               model->setHeaderData(2, Qt::Horizontal, QObject::tr("Joueur noir"));
               model->setHeaderData(3, Qt::Horizontal, QObject::tr("Joueur blanc"));
               model->setHeaderData(4, Qt::Horizontal, QObject::tr("Heure de début"));
               model->setHeaderData(5, Qt::Horizontal, QObject::tr("Heure de fin"));
               model->setHeaderData(6, Qt::Horizontal, QObject::tr("Gagnant"));
               model->setHeaderData(7, Qt::Horizontal, QObject::tr("Num table"));
               model->setHeaderData(8, Qt::Horizontal, QObject::tr("Commentaire"));

}
        return model;

    }

