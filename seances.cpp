#include "seances.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <QObject>
#include <QtDebug>

seances::seances()
{
ID_salle=0;ID_employe=0;Num_salle=0;Capacite_salle=0;Titre_cours="";Niveau_seance="";Date_seance=QDate::currentDate();
}

seances::seances(int ID_salle,int ID_employe ,int Num_salle , int Capacite_salle , QString Titre_cours ,QDate Date_seance, QString Niveau_seance)
{

this->ID_salle=ID_salle; this->ID_employe=ID_employe; this->Num_salle=Num_salle; this->Capacite_salle=Capacite_salle; this->Titre_cours=Titre_cours;
this->Niveau_seance=Niveau_seance;this->Date_seance=Date_seance;
}
int seances::getID_salle(){return ID_salle;}
int seances::getID_employe(){return ID_employe;}
int seances::getNum_salle(){return Num_salle;}
int seances::getCapacite_salle(){return Capacite_salle;}
QString seances::getTitre_cours(){return Titre_cours;}
QString seances::getNiveau_seance(){return Niveau_seance;}
QDate seances::getDate_seance(){return Date_seance;}
void seances::setID_salle(int ID_salle){this->ID_salle=ID_salle;}
void seances::setID_employe(int ID_employe){this->ID_employe=ID_employe;}
void seances::setNum_salle(int Num_salle){this->Num_salle=Num_salle;}
void seances::setCapacite_salle(int Capacite_salle){this->Capacite_salle=Capacite_salle;}
void seances::setTitre_cours(QString Titre_cours){this->Titre_cours=Titre_cours;}
void seances::setNiveau_seance(QString Niveau_seance){this->Niveau_seance=Niveau_seance;}
void seances::setDate_seance(QDate Date_seance){this->Date_seance=Date_seance;}
bool seances::ajouter_S()
 {
     bool test=false;
     QSqlQuery query;
     QString ID_salle_string= QString::number(ID_salle);
     QString ID_employe_string= QString::number(ID_employe);
     QString Num_salle_string= QString::number(Num_salle);
     QString Capacite_salle_string= QString::number(Capacite_salle);
       query.prepare("INSERT INTO seances (ID_salle, Num_salle,ID_employe, Capacite_salle ,Titre_cours,Date_seance,Niveau_seance) "
                     "VALUES (:ID_salle, :Num_salle, :ID_employe,:Capacite_salle,:Titre_cours,:Date_seance,:Niveau_seance)");
       query.bindValue(0,ID_salle_string);
       query.bindValue(1, Num_salle_string);
       query.bindValue(2, ID_employe_string);
       query.bindValue(3, Capacite_salle_string);
       query.bindValue(4, Titre_cours);
       query.bindValue(5, Date_seance);
       query.bindValue(6, Niveau_seance);

       query.exec();
       test =true;
     return test ;
 }
QSqlQueryModel* seances::afficher_S()
{
     QSqlQueryModel* model=new  QSqlQueryModel();

     model->setQuery("SELECT* FROM seances");

    return model;

}
bool seances::modifier_S(){
    bool test=false;
    QSqlQuery query;
    QString ID_salle_string= QString::number(ID_salle);
    QString ID_employe_string= QString::number(ID_employe);
    QString Num_salle_string= QString::number(Num_salle);
    QString Capacite_salle_string= QString::number(Capacite_salle);
      query.prepare("UPDATE seances SET Num_salle=:Num_salle,ID_employe=:ID_employe,Capacite_salle=:Capacite_salle,Titre_cours=:Titre_cours,Date_seance=:Date_seance,Niveau_seance=:Niveau_seance WHERE ID_salle=:ID_salle");
      query.bindValue(":ID_salle",ID_salle_string);
      query.bindValue(":Num_salle", Num_salle_string);
      query.bindValue(":ID_employe", ID_employe_string);
      query.bindValue(":Capacite_salle", Capacite_salle_string);
      query.bindValue(":Titre_cours", Titre_cours);
      query.bindValue(":Date_seance", Date_seance);
      query.bindValue(":Niveau_seance", Niveau_seance);

      query.exec();
      test =true;
    return test ;
}
bool seances::supprimer_S(int ID_salle){

   QSqlQuery query;
     QString res=QString::number(ID_salle);
     query.prepare("DELETE FROM seances WHERE ID_salle = :ID_salle ");
     query.bindValue(":ID_salle",res); //affectation et association des val
     return query.exec();

}
bool seances::verifvidestring(QString S)
{
    bool test=true;
        if(S.length()==0)
         {  test=false;
            return test;}
        return test;
}

bool seances ::verifint(int S)
{
    bool test=true;
        if(S==0)
         {  test=false;
            return test;}
        return test;

}
bool seances ::veriftel(int S)
{
    bool test=true;
        if(S==0)
         {  test=false;
            return test;}
        QString tel_string=QString::number(S);
        if(tel_string.length() == 0 )
         {  test=false;


            return test;}
        return test;

}
bool seances ::verifid(int S)
{
    bool test=true;
        if(S==0)
         {  test=false;
            return test;}
        QString tel_string=QString::number(S);
        if(tel_string.length()!=8)
         {  test=false;


            return test;}
        return test;

}
QSqlQueryModel * seances::afficher_tri_date()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from seances order by Date_seance asc ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_salle"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Num_salle"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_employe"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Capacite_salle"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Titre_cours"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date_seance"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("Niveau_seance"));



    return model;
}

QSqlQueryModel * seances::afficher_tri_capacite()
{QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from seances order by Capacite_salle asc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_salle"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Num_salle"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_employe"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Capacite_salle"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Titre_cours"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date_seance"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Niveau_seance"));



    return model;
}
QSqlQueryModel* seances::chercher_seance(int index,QString text)
{
QSqlQuery query;
    QSqlQueryModel* model=new QSqlQueryModel();
    if(index==0)
   { query.prepare("SELECT * FROM seances where ID_salle like '"+text+"'");
     query.exec();
     model->setQuery(query);
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_salle"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("Num_salle"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_employe"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("Capacite_salle"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("Titre_cours"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date_seance"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("Niveau_seance"));
     }
   if(index==1)
      {
       query.prepare("SELECT * FROM seances where ID_employe like '"+text+"'");
           query.exec();
           model->setQuery(query);
           model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_salle"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("Num_salle"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_employe"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("Capacite_salle"));
           model->setHeaderData(4, Qt::Horizontal, QObject::tr("Titre_cours"));
           model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date_seance"));
           model->setHeaderData(6, Qt::Horizontal, QObject::tr("Niveau_seance"));
   }


    return model;

}


