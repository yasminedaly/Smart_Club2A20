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

commandeh::commandeh()
{
/*id=0;
nom=" ";
prenom="";*/

}
 commandeh::commandeh(int id_commande ,QString nom_c,QString produit_c)
{
    this->id_commande=id_commande;
    this->nom_c=nom_c;
    this->produit_c=produit_c ;
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


bool commandeh::ajoutehis()
{
    QSqlQuery query;
    QString res=QString::number(id_commande);

    query.prepare("INSERT INTO historique (ID_COMMANDE, NOM_C, produit_c) "
                  "VALUES (:ID_COMMANDE, :NOM_C, :produit_c)");
    query.bindValue(":id_commande", res);
    query.bindValue(":NOM_C", nom_c);
    query.bindValue(":produit_c", produit_c);
    return    query.exec();
}

bool commandeh::modifierhis()

{
    QSqlQuery query;
    QString res=QString::number(id_commande);

    query.prepare("UPDATE historique SET  NOM_C='"+nom_c+"' , produit_c ='"+produit_c+"' where id_commande= :id_commande ");
    query.bindValue(":id_commande", res);
    query.bindValue(":NOM_C", nom_c);
    query.bindValue(":produit_c", produit_c);

    return    query.exec();
}


QSqlQueryModel * commandeh::afficherhis()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from historique");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_commande"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_C"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("produit_c"));
        return model;

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
          model->setHeaderData(3, Qt::Horizontal, QObject::tr ("Date_commande"));



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


 /*QSqlQueryModel *commande::Product_type_pro_list()
 {

         QSqlQueryModel * model= new QSqlQueryModel();

         model->setQuery("SELECT TYPE FROM EV");


         return model;*


 }*/

 /*QGraphicsScene *commande::StatPromo_Product_type()
 {


     //Calculer la récurcivité de chaque type de produit
    commande tempcc;
    QString test;

     int max=0;
     int sportif=0;
     int caritatif=0;
     int culturel=0;
     int artistique=0;




     QSqlQueryModel * model=tempcc.Product_type_pro_list();


     max=model->rowCount();

     for (int i=0;i<model->rowCount();i++)
     {
         test=model->record(i).value(0).toString();





         if(test=="sportif")
         {
             sportif++;
         }
         else if(test=="caritatif")
         {
             caritatif++;

         }
         else if(test=="culturel")
         {
             culturel++;

         }
         else if(test=="artistique")
         {
             artistique++;
         }


   }





 //Génrer la Statistique sur La QGraphiqueView


     QGraphicsScene *  scene = new QGraphicsScene();

     QGraphicsEllipseItem *ellipse1;
     QGraphicsEllipseItem *ellipse2;
     QGraphicsEllipseItem *ellipse3;
     QGraphicsEllipseItem *ellipse4;



     QGraphicsTextItem *tex1;
     QGraphicsTextItem *tex2;
     QGraphicsTextItem *tex3;
     QGraphicsTextItem *tex4;


     QGraphicsRectItem *rec1;
     QGraphicsRectItem *rec2;
     QGraphicsRectItem *rec3;
     QGraphicsRectItem *rec4;




     QBrush greenBrush(Qt::green);
     QBrush redBrush(Qt::red);
     QBrush yellowBrush(Qt::yellow);
     QBrush bleuBrush(Qt::blue);
     QPen outlinePen(Qt::black);
     outlinePen.setWidth(1);

     int x=200;
     int y=100;
     int w=250;
     int h=250;


     ellipse1 = scene->addEllipse(x, y, w, h);
     ellipse1->setBrush(greenBrush);
     ellipse1->setStartAngle(((sportif*360)/max)*16);




     ellipse2 = scene->addEllipse(x, y, w, h);
     ellipse2->setBrush(redBrush);
     ellipse1->setStartAngle(((sportif*360)/max)*16);
     ellipse2->setSpanAngle(((caritatif*360)/max)*16);


     ellipse3 = scene->addEllipse(x, y, w, h);
     ellipse3->setBrush(yellowBrush);
     ellipse3->setStartAngle((((sportif+caritatif)*360)/max)*16);
     ellipse3->setSpanAngle(((culturel*360)/max)*16);



     ellipse4 = scene->addEllipse(x, y, w, h);
     ellipse4->setBrush(bleuBrush);
     ellipse4->setStartAngle((((sportif+caritatif+culturel)*360)/max)*16);
     ellipse4->setSpanAngle(((artistique*360)/max)*16);






     float sportif_pourcentage=((((sportif*360)/max))*100)/360;
     float caritatif_pourcentage=((((caritatif*360)/max))*100)/360;
     float culturel_pourcentage=((((culturel*360)/max))*100)/360;
     float artistique_pourcentage=((((artistique*360)/max))*100)/360;









     QString sportif_convert=QString::number( sportif_pourcentage);
     QString caritatif_convert=QString::number(caritatif_pourcentage);
     QString culturel_convert=QString::number(culturel_pourcentage);
     QString artistique_convert=QString::number(artistique_pourcentage);



     rec1 = scene->addRect(-20, 2, 20, 20, outlinePen, greenBrush);
     rec2 = scene->addRect(-20, 42, 20, 20, outlinePen, redBrush);
     rec3 = scene->addRect(-20, 80, 20, 20, outlinePen, yellowBrush);
     rec4 = scene->addRect(-20, 120, 20, 20, outlinePen, bleuBrush);



     tex1 = scene->addText("Event sportif : "+sportif_convert+"%", QFont("Arial", 11));
     tex2 = scene->addText("\n\nEvent caritatif : "+caritatif_convert+"%", QFont("Arial", 11) );
     tex3 = scene->addText("\n\n\n\nEvent culturel: "+culturel_convert+"%", QFont("Arial", 11) );
     tex4 = scene->addText("\n\n\n\n\n\nEvent artistique : "+artistique_convert+"%", QFont("Arial", 11) );




     return scene;


 }*/

