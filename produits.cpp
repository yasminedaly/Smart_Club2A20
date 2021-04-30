#include "produits.h"
#include <QSqlQuery>
#include <QSqlQueryModel>

Produits::Produits()
{
    ID_Produit = 0 ;
    Nom_Produit = "" ;
    Quantite_Produit = 0 ;
    Prix_Produit = 0 ;
}

Produits::Produits(int ID_Produit, QString Nom_Produit, int Quantite_Produit, float Prix_Produit)
{
    this-> ID_Produit = ID_Produit ;
    this-> Nom_Produit = Nom_Produit ;
    this-> Quantite_Produit = Quantite_Produit ;
    this-> Prix_Produit = Prix_Produit ;
}

void Produits::Set_iD_Produit(int ID_Produit)
{
    this-> ID_Produit = ID_Produit ;
}

void Produits::Set_Nom_Produit(QString Nom_Produit)
{
    this-> Nom_Produit = Nom_Produit ;
}

void Produits::Set_Quantite_Produit(int Quantite_Produit)
{
    this-> Quantite_Produit = Quantite_Produit ;
}

void Produits::Set_Prix_Produit(float Prix_Produit)
{
    this-> Prix_Produit = Prix_Produit ;
}


int Produits::Get_ID_Produit()
{
    return ID_Produit ;
}

QString Produits::Get_Nom_Produit()
{
    return Nom_Produit ;
}

int Produits::Get_Quantite_Produit()
{
    return Quantite_Produit ;
}

float Produits::Get_Prix_Produit()
{
    return Prix_Produit ;
}



bool Produits::Verifier_ID(int ID_Produit)
{
    QSqlQuery  query;
        bool test=false;
          QString ID=QString::number(ID_Produit);
            query.prepare("SELECT * from produits where ID_Produit=:ID_Produit");
            query.bindValue(":ID_Produit",ID);

            if(query.exec() && query.next())
                {
                        test=true;
                        return test;
                }
        return test;
}



bool Produits::Verifier_QString_Vide(QString Ch)
{
    bool test=true;
        if(Ch.length()==0)
         {
            test=false;
            return test;
         }
            return test;
}



bool Produits::Verifier_Int(int x )
{
    bool test=true;
        if(x==0 || x<0 )
         {  test=false;
            return test;
         }
        return test;
}



bool Produits::ajouter_Produit()
{
    QSqlQuery query ;
    QString res=  QString::number(ID_Produit);
    QString res2= QString::number(Quantite_Produit);
    QString res3= QString::number(Prix_Produit);

    query.prepare("insert into produits (ID_Produit,Nom_Produit,Quantite_Produit,Prix_Produit)""values( :ID_Produit , :Nom_Produit ,:Quantite_Produit ,  :Prix_Produit)") ;

    query.bindValue(":ID_Produit",res);
    query.bindValue(":Nom_Produit",Nom_Produit);
    query.bindValue(":Quantite_Produit",res2);
    query.bindValue(":Prix_Produit",res3);

    return query.exec();
}



QSqlQueryModel * Produits::afficher_Produit()
{
    QSqlQueryModel *model = new QSqlQueryModel ;

    model->setQuery("select * from produits") ;
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_Produit"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom_Produit"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Quantite_Produit"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prix_Produit"));

    return model ;
}


bool Produits::supprimer_Produit(int ID_Produit)
{
    QSqlQuery query ;
    QString res= QString::number(ID_Produit);

    query.prepare("Delete from produits where ID_Produit= :ID_Produit");
    query.bindValue(":ID_Produit",res);

    return query.exec();
}


bool Produits::modifier_Produit(int ID_Produit, QString Nom_Produit, int Quantite_Produit, float Prix_Produit)
{
    QSqlQuery query ;
    QString res=  QString::number(ID_Produit);
    QString res2= QString::number(Quantite_Produit);
    QString res3= QString::number(Prix_Produit);

    query.prepare(" UPDATE produits SET ID_Produit='"+res+"' , Nom_Produit='"+Nom_Produit+"',Quantite_Produit='"+res2+"',Prix_Produit='"+res3+"' where ID_Produit=:ID_Produit ") ;

    query.bindValue(":ID_Produit",res);
    query.bindValue(":Nom_Produit",Nom_Produit);
    query.bindValue(":Quantite_Produit",res2);
    query.bindValue(":Prix_Produit",res3);


    return query.exec();
}


QSqlQueryModel * Produits::Recherche_ID(QString id)
   {
    QSqlQueryModel * model= new QSqlQueryModel();


    model->setQuery("select * from produits where ID_Produit like '%"+id+"%' ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_Produit"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom_Produit"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Quantite_Produit"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prix_Produit"));

        return model;
    }

QSqlQueryModel * Produits::Recherche_Nom(QString Nom)
{
 QSqlQueryModel * model= new QSqlQueryModel();


 model->setQuery("select * from produits where Nom_Produit like '%"+Nom+"%' ");
 model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_Produit"));
 model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom_Produit"));
 model->setHeaderData(2,Qt::Horizontal,QObject::tr("Quantite_Produit"));
 model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prix_Produit"));

     return model;
 }

QSqlQueryModel * Produits::Recherche_Quantite(QString Quantite)
{
 QSqlQueryModel * model= new QSqlQueryModel();


 model->setQuery("select * from produits where Quantite_Produit like '%"+Quantite+"%' ");
 model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_Produit"));
 model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom_Produit"));
 model->setHeaderData(2,Qt::Horizontal,QObject::tr("Quantite_Produit"));
 model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prix_Produit"));

     return model;
 }

QSqlQueryModel * Produits::Recherche_Prix(QString Prix)
{
 QSqlQueryModel * model= new QSqlQueryModel();


 model->setQuery("select * from produits where Prix_Produit like '%"+Prix+"%' ");
 model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_Produit"));
 model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom_Produit"));
 model->setHeaderData(2,Qt::Horizontal,QObject::tr("Quantite_Produit"));
 model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prix_Produit"));

     return model;
 }

int Produits::PK_Check(QString id_Prod)
{
    int rows ;
    QSqlQuery query;

        query.prepare("Select count(*) from produits where ID_Produit like '"+id_Prod+"' ");
        query.bindValue(":ID_Produit", id_Prod);
        query.exec();
        rows= 0;
        if (query.next())
         {
            rows= query.value(0).toInt();
         }
    return rows;
}

QStringList Produits::listeProduits(){
     QSqlQuery query;
     query.prepare("select ID_Produit from produits ");
     query.exec();
     QStringList list;
     while(query.next()){
         list.append(query.value(0).toString());
     }

     return list;
 }
