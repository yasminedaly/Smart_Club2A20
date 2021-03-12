#include "evenement.h"
#include <QSqlQuery>
#include <QtDebug>
//#include <QSqlQueryModel>
#include <QObject>

Evenement::Evenement()
{
/*id=0;
nom=" ";
prenom="";*/

}
Evenement::Evenement (int id , QString nom, QString adresse , int num , int nb , QString date)
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
//yassmine

/*bool EVENEMENT::verifierid(int id)
{  QSqlQuery  query;
    bool test=false;
      QString res=QString::number(id);
        query.prepare("SELECT * from joueurs where id=:id");
         query.bindValue(":id",res);
    if(query.exec()&&query.next())
    {     test=true;
         return test;
    }
    return test;
}

bool EVENEMENT::verifvidestring(QString S)
{
    bool test=true;
        if(S.length()==0)
         {  test=false;
            return test;}
        return test;
}

bool EVENEMENT ::verifint(int S)
{
    bool test=true;
        if(S==0)
         {  test=false;
            return test;}
        return test;

} */
// fin yassmine
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




 bool Evenement::modifier (int id , QString nom, QString adresse , int num , int nb , QString date)
     {





    QString res=QString::number(id);
     QSqlQuery query;
   // query.prepare ( " UPDATE  Evenement SET  nom =(?),adresse=(?),num=(?),nb =(?), date_event=(?) WHERE id =(?) " );

     query.prepare(" UPDATE  Evenement SET  nom =:nom,adresse=:adresse,num=:num,nb =:nb, date_event=:date  WHERE id =: id " );

     query.bindValue(":id", res );
     query.bindValue(":nom", nom);
     query.bindValue(":adresse", adresse);
     query.bindValue(":num", num);
     query.bindValue(":nb", nb);
     query.bindValue(":date", date);

      return query.exec();

 }
// query.prepare ( " UPDATE  Evenement SET  nom =(?),adresse=(?),num=(?),nb =(?), date_event=(?) WHERE id =(?) " );

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

     model->setQuery("select * from Evenement order by ID");
     model->setHeaderData(0, Qt::Horizontal,QObject::tr ("ID"));

     model->setHeaderData(1, Qt::Horizontal,QObject::tr ("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr ("adresse"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr ("num"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr ("nb"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr ("date"));

         return model;
     }

