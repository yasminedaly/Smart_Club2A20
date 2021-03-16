#include "commande.h"
#include <QSqlQuery>
#include <QtDebug>
//#include <QSqlQueryModel>
#include <QObject>

commande::commande()
{
/*id=0;
nom=" ";
prenom="";*/

}
commande::commande ( int id_commande, int nb_produit, float Prix_t, QString Date_commande )
    {
    this->id_commande=id_commande ;
    this->nb_produit=nb_produit ;
    this->Prix_t=Prix_t;
    this->Date_commande=Date_commande;
    }

//int Etudiant::getid (){return id;}
//QString Etudiant::getnom() {return nom;}
//QString Etudiant:: getprenom() {return prenom;}

//void Etudiant::setid (int id){this->id=id;}
//void Etudiant::setnom (QString nom){this->nom=nom;}
//void Etudiant::setprenom (QString prenom) {this->prenom=prenom ;}

bool commande::ajouter ()
    {



    QSqlQuery query;

   QString res=QString::number(id_commande);
   QString res2=QString::number(nb_produit);
 QString resf=QString::number(Prix_t);

    query.prepare("INSERT INTO COMMANDE (ID_COMMANDE, NB_PRODUIT,PRIX_T,DATE_COMMANDE) " "VALUES (:id_commande, :nb_produit, :Prix_t ,:Date_commande)");

    query.bindValue(":id_commande", res );
    query.bindValue(":nb_produit", res2 );
    query.bindValue(":Prix_t", resf);
    query.bindValue(":Date_commande", Date_commande);

     return query.exec();

}

 bool commande::supprimer(int id_commande)
    {

        QSqlQuery query;
        QString res=QString::number(id_commande);

     query.prepare("Delete from COMMANDE  where id_commande= :id_commande ");

     query.bindValue(":id_commande", res );

       return query.exec();

    }

 QSqlQueryModel * commande::afficher()

    {


     QSqlQueryModel *model = new QSqlQueryModel ();

          model->setQuery("SELECT * FROM COMMANDE");

           model->setHeaderData(0, Qt::Horizontal,QObject::tr ("id_commande"));

          model->setHeaderData(1, Qt::Horizontal,QObject::tr ("nb_produit"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr ("Prix_t"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr ("Date_commande"));



     return model ;


  }
 bool commande::modifier(int id_commande,int nb_produit, float Prix_t, QString Date_commande)
 {
        QSqlQuery query;

        QString res=QString::number(id_commande);
        QString res2=QString::number(nb_produit);
      QString resf=QString::number(Prix_t);

         query.prepare("UPDATE commande SET id_commande='"+res+"', nb_produit='"+res2+"' , Prix_t ='"+resf+"' , Date_commande ='"+Date_commande+"' where id_commande= :id_commande ");



         query.bindValue(":id_commande", res );
         query.bindValue(":nb_produit", res2 );
         query.bindValue(":Prix_t", resf);
         query.bindValue(":Date_commande", Date_commande);

          return query.exec();



    }

 bool commande::rechercher(int id_commandeA)
 {
     QSqlQuery query;
      QString res3=QString::number(id_commandeA);

 query.prepare("SELECT id_commande FROM commande WHERE id_commande=:id_commandeA ");
 query.bindValue(":id_commande", res3);

 return   query.exec();
 }


 QSqlQueryModel * commande::tri()
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from commande order by id_commande asc;");
     model->setHeaderData(0, Qt::Horizontal,QObject::tr ("id_commande"));

    model->setHeaderData(1, Qt::Horizontal,QObject::tr ("nb_produit"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr ("Prix_t"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr ("Date_commande"));
         return model;
 }



