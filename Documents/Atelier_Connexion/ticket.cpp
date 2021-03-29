#include "ticket.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
#include<QVariant>

Ticket::Ticket()
{
}
Ticket::Ticket (int id_ticket , int id_evenement , QString type_acheteur , QString type ,  int prix , QDate date_achat)
    {
    this->id_ticket=id_ticket ;
    this->id_evenement=id_evenement ;
    this->type_acheteur=type_acheteur ;
     this->type=type;
    this->prix=prix ;
     this->date_achat=date_achat ;
    }



bool Ticket::ajouter ()
    {



    QSqlQuery query;

   QString res=QString::number(id_ticket);
   QString res1=QString::number(id_evenement);



query.prepare("INSERT INTO TICKET  (id_ticket, id_evenement, type_acheteur, type , prix , date_achat) " "VALUES (:id_ticket, :id_evenement, :type_acheteur, :type, :prix, :date_achat)");

   query.bindValue(":id_ticket", res );
    query.bindValue(":id_evenement", res1);
    query.bindValue(":type_acheteur", type_acheteur);
    query.bindValue(":type", type);
    query.bindValue(":prix", prix);
    query.bindValue(":date_achat", date_achat);

     return query.exec();

}

 bool Ticket::supprimer(int id_ticket)
    {

     QString res=QString::number(id_ticket);
     QSqlQuery query;
     query.prepare("Delete from TICKET  where Id_ticket= :id_ticket ");
     query.bindValue(":id_ticket", res );
       return query.exec();

    }

 QSqlQueryModel * Ticket::afficher()

    {


     QSqlQueryModel *model = new QSqlQueryModel ();

          model->setQuery("SELECT * FROM Ticket");

          model->setHeaderData(0, Qt::Horizontal,QObject::tr ("ID_ticket"));

          model->setHeaderData(1, Qt::Horizontal,QObject::tr ("id_evenement"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr ("type_acheteur"));

          model->setHeaderData(3, Qt::Horizontal, QObject::tr ("type_ticket"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr ("prix"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr ("date_achat"));

     return model ;


  }
 QSqlQueryModel * Ticket::recherche(const QString &aux)
 {
     QSqlQueryModel * model = new QSqlQueryModel();

     model->setQuery("select * from Ticket where ((type_acheteur ) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr ("ID_ticket"));

    model->setHeaderData(1, Qt::Horizontal,QObject::tr ("id_evenement"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr ("type_acheteur"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr ("type_ticket"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr ("prix"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr ("date_achat"));
     return model;
 }

 bool Ticket::modifier_Ticket(int id_ticket , int id_evenement , QString type_acheteur , QString type ,  int prix , QDate date_achat)
 {
     QSqlQuery query;

    QString res=QString::number(id_ticket);
    QString res1=QString::number(id_evenement);

     query.prepare(" UPDATE Ticket SET id_ticket=:id_ticket , id_evenement=:id_evenement,type_acheteur=:type_acheteur,type=:type,prix=:prix, date_achat=:date_achat where id_ticket=:id_ticket ") ;

     query.bindValue(":id_ticket", res );
      query.bindValue(":id_evenement", res1);
      query.bindValue(":type_acheteur", type_acheteur);
      query.bindValue(":type", type);
      query.bindValue(":prix", prix);
      query.bindValue(":date_achat", date_achat);

     return query.exec();
 }


 Ticket Ticket::getTicket(int id_ticket){
     QString res=QString::number(id_ticket);
     QString res1=QString::number(id_evenement);
     QSqlQuery query;
      query.prepare("select * from Ticket  WHERE id_ticket=:id_ticket");

      query.bindValue(":id_ticket", res );

      query.exec();
      Ticket T;

      while(query.next()){
          qDebug()<< query.value(1).toInt();
        T.setid_ticket(query.value(0).toInt());
        T.setid_evenement(query.value(1).toInt());
        T.settype_acheteur(query.value(2).toString());
        T.settype(query.value(3).toString());
        T.setprix(query.value(4).toInt());
        T.setdate_achat(query.value(5).toDate());
      }


      return T;

}
 int Ticket::calculeTicket(int id_event){
     QString res=QString::number(id_event);
     QSqlQuery query;
      query.prepare("select * from Ticket  WHERE id_evenement=:id_evenement");
      query.bindValue(":id_evenement", res );
      query.exec();
       int total=0;

      while(query.next()){
        total++;

      }


      return total;
 }

 QSqlQueryModel *Ticket:: afficher_trie()
  {

     QSqlQueryModel * model= new QSqlQueryModel();

     model->setQuery("select * from Ticket order by id_ticket ASC");
     model->setHeaderData(0, Qt::Horizontal,QObject::tr ("id_ticket"));

     model->setHeaderData(1, Qt::Horizontal,QObject::tr ("id_evenement"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr ("type_acheteur"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr ("type_ticket"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr ("prix"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr ("date_achat"));

         return model;
     }

