#include "bibliotheques.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include<QDialog>
#include <QPrinter>
#include<QPrintDialog>



Bibliotheques::Bibliotheques()
{


}

Bibliotheques::Bibliotheques ( int id_l, QString nom_l, QString Ref_livre ,QString desc_l ,QString date_s ,QString date_r ,QString displ,QString displ1  )


    {
    this->id_l=id_l ;
    this->nom_l=nom_l ;
    this->Ref_livre =Ref_livre ;
    this->desc_l=desc_l;
    this->date_s =date_s ;
    this-> date_r= date_r;
    this->displ=displ;
      this->displ1=displ1 ;




    }

bool Bibliotheques::ajouter_livre()
    {



    QSqlQuery query;

   QString res=QString::number(id_l);




    query.prepare("INSERT INTO BIBLIOTHEQUE (id_l , nom_l , Ref_livre , desc_l , date_s , date_r , displ , displ1  ) " "VALUES (:id_l ,:nom_l ,:Ref_livre ,:desc_l ,:date_s ,:date_r ,:displ , :displ1   )");

    query.bindValue(":id_l", res );
    query.bindValue(":nom_l",  nom_l );
    query.bindValue(":Ref_livre", Ref_livre);
    query.bindValue(":desc_l", desc_l);
    query.bindValue(":date_s", date_s);
    query.bindValue(":date_r", date_r);



    query.bindValue(":displ", displ);
    query.bindValue(":displ1", displ1);






     return query.exec();

}

    QSqlQueryModel* Bibliotheques::afficher_livre ()

   {


    QSqlQueryModel *model = new QSqlQueryModel ();

         model->setQuery("SELECT * FROM BIBLIOTHEQUE");

         model->setHeaderData(0, Qt::Horizontal,QObject::tr ("id_l"));
         model->setHeaderData(1, Qt::Horizontal,QObject::tr ("nom_l"));

         model->setHeaderData(2, Qt::Horizontal,QObject::tr ("Ref_livre"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr ("desc_l"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr ("date_s"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr ("date_r"));
         model->setHeaderData(6, Qt::Horizontal, QObject::tr ("displ"));
         model->setHeaderData(7, Qt::Horizontal, QObject::tr ("displ1"));


    return model ;


 }

    bool Bibliotheques::supprimer_livre(int id_l)
       {

           QSqlQuery query;
           QString res=QString::number(id_l);

        query.prepare("Delete from Bibliotheque  where id_l= :id_l ");

        query.bindValue(":id_l", res );

          return query.exec();

       }

    bool Bibliotheques::modifier_livre(int id_l, QString nom_l, QString Ref_livre ,QString desc_l ,QString date_s ,QString date_r ,QString displ,QString displ1)
    {
           QSqlQuery query;

            QString res=QString::number(id_l);

            query.prepare("UPDATE Bibliotheque SET id_l='"+res+"', nom_l='"+nom_l+"' , Ref_livre ='"+Ref_livre+"' , desc_l ='"+desc_l+"' , date_s='"+date_s+"' , date_r ='"+date_r+"' , displ ='"+displ+"' , displ1 ='"+displ1+"' where id_l= :id_l ");



            query.bindValue(":id_l", res );
            query.bindValue(":nom_l",  nom_l );
            query.bindValue(":Ref_livre", Ref_livre);
            query.bindValue(":desc_l", desc_l);
            query.bindValue(":date_s", date_s);
            query.bindValue(":date_r", date_r);



            query.bindValue(":displ", displ);
            query.bindValue(":displ1", displ1);


             return query.exec();



       }


    bool Bibliotheques::rechercher_livre(int id_lA)
    {
        QSqlQuery query;
         QString res=QString::number(id_lA);

    query.prepare("SELECT id_l FROM BIBLIOTHEQUE WHERE id_l=:id_lA ");
    query.bindValue(":id_l", res);

    return   query.exec();
    }



    QSqlQueryModel * Bibliotheques::tri_livre()
    {
        QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from Bibliotheque order by id_l asc;");

        model->setHeaderData(0, Qt::Horizontal,QObject::tr ("id_l"));
        model->setHeaderData(1, Qt::Horizontal,QObject::tr ("nom_l"));

        model->setHeaderData(2, Qt::Horizontal,QObject::tr ("Ref_livre"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr ("desc_l"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr ("date_s"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr ("date_r"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr ("displ"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr ("displ1"));

            return model;
    }

    QSqlQueryModel * Bibliotheques::tri2(QString n )
    {


        {
            QSqlQueryModel * model= new QSqlQueryModel();

            if(n=="id_l")
                model->setQuery("select * from Bibliotheque order by id_l asc;");
            else if(n=="nom_l")
                model->setQuery("select * from Bibliotheque order by nom_l asc;");
            else if (n=="date_s")
                model->setQuery("SELECT * FROM BIBLIOTHEQUE ORDER BY date_s asc;");

            model->setHeaderData(0, Qt::Horizontal,QObject::tr ("id_l"));
            model->setHeaderData(1, Qt::Horizontal,QObject::tr ("nom_l"));

            model->setHeaderData(2, Qt::Horizontal,QObject::tr ("Ref_livre"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr ("desc_l"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr ("date_s"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr ("date_r"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr ("displ"));
            model->setHeaderData(7, Qt::Horizontal, QObject::tr ("displ1"));

                return model;
        }



    }


    bool Bibliotheques::controlSaisieCharVide(QString nom_l,QString nom_ll)

    {

     if(nom_l.length()!=0)
     {
             return true;
        }

        else
        {
            QMessageBox::critical(nullptr, QObject::tr("nom_l"),
                        QObject::tr("Le champs nom livre est vide.\n"
                                    "Click Cancel to exit.").arg(nom_ll), QMessageBox::Cancel);
            return false;
        }

    }

    bool Bibliotheques::controlsaisieRef(QString saisi){
        int i,test1=0,test2=0;


                for (i=0;i<saisi.length();i++)
                {
         if( saisi[i]=="C")
              test1=1;
         if( saisi[i]=="M")
             test2=1;
                }
        if((test1==1)&&(test2==1)){
            return true;
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Ref_livre"),
                        QObject::tr("Ref_livre non valid.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            return false;
        }


    }

    QSqlQueryModel * Bibliotheques::chercher_matpar_nom(QString nom_l)
     {

        {QSqlQueryModel *model = new QSqlQueryModel;
            model->setQuery("SELECT * FROM Bibliotheque WHERE NOMR='"+nom_l+"' ");
            model->setHeaderData(0, Qt::Horizontal,QObject::tr ("id_l"));
            model->setHeaderData(1, Qt::Horizontal,QObject::tr ("nom_l"));

            model->setHeaderData(2, Qt::Horizontal,QObject::tr ("Ref_livre"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr ("desc_l"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr ("date_s"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr ("date_r"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr ("displ"));
            model->setHeaderData(7, Qt::Horizontal, QObject::tr ("displ1"));

            return model ;
        }

     }

    QSqlQueryModel *Bibliotheques::chercher_matpar_ref(QString Ref_livre)

     {

        {
            QSqlQueryModel *model = new QSqlQueryModel;
            model->setQuery("SELECT * FROM Bibliotheque WHERE Ref_livre='"+Ref_livre+"' ");
            model->setHeaderData(0, Qt::Horizontal,QObject::tr ("id_l"));
            model->setHeaderData(1, Qt::Horizontal,QObject::tr ("nom_l"));

            model->setHeaderData(2, Qt::Horizontal,QObject::tr ("Ref_livre"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr ("desc_l"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr ("date_s"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr ("date_r"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr ("displ"));
            model->setHeaderData(7, Qt::Horizontal, QObject::tr ("displ1"));

            return model ;
        }
    }

