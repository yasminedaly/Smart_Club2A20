#include "evenement.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
#include<QVariant>

Evenement::Evenement()
{}
Evenement::Evenement (int id , QString nom, QString adresse , int num , int nb , QDate date)
    {
    this->id=id ;
    this->nom=nom ;
    this->adresse=adresse ;
    this->num=num ;
    this->nb=nb ;
    this->date=date;
    }



bool Evenement::ajouter ()
    {



    QSqlQuery query;

   QString res=QString::number(id);

    query.prepare("INSERT INTO EVENEMENT  (id, nom, adresse, num, nb, date_event) " "VALUES (:id, :nom, :adresse, :num, :nb, :date)");

    query.bindValue(":id", res );
    query.bindValue(":nom", nom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":num", num);
    query.bindValue(":nb", nb);
    query.bindValue(":date", date);

     return query.exec();

}

 bool Evenement::supprimer(int id)
    {

     QString res=QString::number(id);
     QSqlQuery query;
     query.prepare("Delete from Evenement  where Id= :id ");
     query.bindValue(":id", res );
       return query.exec();

    }

 QSqlQueryModel * Evenement::afficher()

    {


     QSqlQueryModel *model = new QSqlQueryModel ();

          model->setQuery("SELECT * FROM Evenement");

           model->setHeaderData(0, Qt::Horizontal,QObject::tr ("ID"));

          model->setHeaderData(1, Qt::Horizontal,QObject::tr ("nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr ("adresse"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr ("num"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr ("nb"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr ("date"));


     return model ;


  }




 bool Evenement::modifier (int id , QString nom, QString adresse , int num , int nb , QDate date)
     {





    QString res=QString::number(id);
     QSqlQuery query;
     query.prepare(" UPDATE  Evenement SET nom =:nom,adresse=:adresse,num=:num,nb=:nb, date_event=:date  WHERE id =:id " );

     query.bindValue(":id", res );
     query.bindValue(":nom", nom);
     query.bindValue(":adresse", adresse);
     query.bindValue(":num", num);
     query.bindValue(":nb", nb);
     query.bindValue(":date", date);

      return query.exec();

 }

 QSqlQueryModel * Evenement::recherche(const QString &aux)
 {
     QSqlQueryModel * model = new QSqlQueryModel();

     model->setQuery("select * from Evenement where ((nom ) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr ("ID"));

    model->setHeaderData(1, Qt::Horizontal,QObject::tr ("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr ("adresse"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr ("num"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr ("nb"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr ("date"));
     return model;
 }
 QSqlQueryModel *Evenement:: afficher_trie()
  {

     QSqlQueryModel * model= new QSqlQueryModel();

     model->setQuery("select * from Evenement order by ID ASC");
     model->setHeaderData(0, Qt::Horizontal,QObject::tr ("ID"));

     model->setHeaderData(1, Qt::Horizontal,QObject::tr ("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr ("adresse"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr ("num"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr ("nb"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr ("date"));

         return model;
     }

 Evenement Evenement::getEvenement(int id){
     QString res=QString::number(id);
      QSqlQuery query;
      query.prepare("select * from evenement  WHERE id=:id");

      query.bindValue(":id", res );

      query.exec();
      Evenement e;

      while(query.next()){
          qDebug()<< query.value(1).toInt();
        e.setid(query.value(0).toInt());
        e.setnom(query.value(1).toString());
        e.setadresse(query.value(2).toString());
        e.setnum(query.value(3).toInt());
        e.setnb(query.value(4).toInt());
        e.setdate(query.value(5).toDate());
      }


      return e;

 }

 QStringList Evenement::listeEvents(){
     QSqlQuery query;
     query.prepare("select id from evenement");
     query.exec();
     QStringList list;
     while(query.next()){
         list.append(query.value(0).toString());
     }

     return list;
 }
