#include "etudiant.h"
#include <QSqlQuery>
#include <QtDebug>
//#include <QSqlQueryModel>
#include <QObject>

Etudiant::Etudiant()
{
/*id=0;
nom=" ";
prenom="";*/

}
Etudiant::Etudiant (int id , QString nom, QString prenom)
    {
    this->id=id ;
    this->nom=nom ;
    this->prenom=prenom ;
    }

//int Etudiant::getid (){return id;}
//QString Etudiant::getnom() {return nom;}
//QString Etudiant:: getprenom() {return prenom;}

//void Etudiant::setid (int id){this->id=id;}
//void Etudiant::setnom (QString nom){this->nom=nom;}
//void Etudiant::setprenom (QString prenom) {this->prenom=prenom ;}

bool Etudiant::ajouter ()
    {



    QSqlQuery query;

   QString res=QString::number(id);

    query.prepare("INSERT INTO ETUDIANT  (id, nom, prenom) " "VALUES (:id, :nom, :prenom)");

    query.bindValue(":id", res );
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);

     return query.exec();

}

 bool Etudiant::supprimer(int id)
    {

     QString res=QString::number(id);
     QSqlQuery query;
     query.prepare("Delete from ETUDIANT  where Id= :id ");
     query.bindValue(":id", res );
       return query.exec();

    }

 QSqlQueryModel * Etudiant::afficher()

    {


     QSqlQueryModel *model = new QSqlQueryModel ();

          model->setQuery("SELECT * FROM etudiant");

           model->setHeaderData(0, Qt::Horizontal,QObject::tr ("ID"));

          model->setHeaderData(1, Qt::Horizontal,QObject::tr ("nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr ("prenom"));


     return model ;


  }




