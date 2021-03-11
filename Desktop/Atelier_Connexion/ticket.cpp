#include "ticket.h"
#include <QSqlQuery>
#include <QtDebug>
//#include <QSqlQueryModel>
#include <QObject>

Ticket::Ticket()
{
/*id=0;
nom=" ";
prenom="";*/

}
Ticket::Ticket (int id_ticket , int id_evenement , QString type_acheteur , QString type ,  int prix , QString date_achat)
//Ticket::Ticket (int id_ticket , int id_evenement , QString type_acheteur , QString type , float prix , QString date_achat)
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


  // query.prepare("INSERT INTO TICKET  (id_ticket, id_evenement, type_acheteur, type_ticket, prix, date_achat) " "VALUES (:id_ticket, :id_evenement, :type_acheteur, :type_ticket, :prix, :date_achat)");
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




