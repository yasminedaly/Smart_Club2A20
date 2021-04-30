#include "factures.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QDate>

Factures::Factures()
{
    ID_Facture = 0 ;
    ID_Fournisseur_Facture = 0 ;
    Total_Facture = 0 ;
    ID_Produit_Facture = 0 ;
    Date_Facture = "" ;
    Etat_Facture = "non" ;
    Quantite_Facture = 0 ;
}

Factures::Factures(int ID_Facture,int ID_Fournisseur_Facture,float Total_Facture ,int ID_Produit_Facture,QString Date_Facture,QString Etat_Facture , int Quantite_Facture)
{
    this->ID_Facture = ID_Facture ;
    this->ID_Fournisseur_Facture = ID_Fournisseur_Facture ;
    this->Total_Facture = Total_Facture ;
    this->ID_Produit_Facture = ID_Produit_Facture ;
    this->Date_Facture = Date_Facture ;
    this->Etat_Facture = Etat_Facture ;
    this->Quantite_Facture = Quantite_Facture ;

}

void Factures::Set_ID_Facture(int ID_Facture)
{
    this->ID_Facture=ID_Facture;
}

void Factures::Set_ID_Fournisseur_Facture(int ID_Fournisseur_Facture)
{
    this->ID_Fournisseur_Facture=ID_Fournisseur_Facture;
}

void Factures::Set_Total_Facture(float Total_Facture)
{
    this->Total_Facture=Total_Facture;
}

void Factures::Set_ID_Produit_Facture(int ID_Produit_Facture)
{
    this->ID_Produit_Facture=ID_Produit_Facture;
}

void Factures::Set_Date_Facture(QString Date_Facture)
{
    this->Date_Facture=Date_Facture;
}

void Factures::Set_Etat_Facture(QString Etat_Facture)
{
    this->Etat_Facture=Etat_Facture;
}

void Factures::Set_Quantite_Facture(int Quantite_Facture)
{
    this->Quantite_Facture=Quantite_Facture;
}



int Factures::Get_ID_Facture()
{
    return ID_Facture;
}

int Factures::Get_ID_Fournisseur_Facture()
{
    return ID_Fournisseur_Facture;
}

float Factures::Get_Total_Facture()
{
    return Total_Facture;
}

int Factures::Get_Quantite_Facture()
{
    return Quantite_Facture;
}


int Factures::Get_ID_Produit_Facture()
{
    return ID_Produit_Facture;
}

QString Factures::Get_Date_Facture()
{
    return Date_Facture;
}

QString Factures::Get_Etat_Facture()
{
    return Etat_Facture;
}


bool Factures::Verifier_ID(int ID_Facture)
{
    QSqlQuery  query;
        bool test=false;
          QString ID=QString::number(ID_Facture);
            query.prepare("SELECT * from factures where ID_Facture=:ID_Facture");
            query.bindValue(":ID_Facture",ID);
        if(query.exec()&&query.next())
        {
             test=true;
             return test;
        }
        return test;
}

bool Factures::Verifier_QString_Vide(QString Ch)
{
    bool test=true;
        if(Ch.length()==0)
         {
            test=false;
            return test;
         }
        return test;
}

bool Factures::Verifier_INT(int x)
{
    bool test=true;
        if(x==0 || x<0 )
         {
            test=false;
            return test;
         }
        return test;
}



bool Factures::ajouter_Facture()
{
    QSqlQuery query ;
    QString res=  QString::number(ID_Facture);
    QString res2= QString::number(ID_Fournisseur_Facture);
    QString res3= QString::number(Total_Facture);
    QString res4= QString::number(Quantite_Facture);
    QString res5= QString::number(ID_Produit_Facture);
    QDate datum =QDate::fromString(Date_Facture,"dd/MM/yyyy");

    query.prepare("insert into factures (ID_Facture,ID_Fournisseur_Facture,Total_Facture,ID_Produit_Facture,Date_Facture,Etat_Facture,Quantite_Facture)"""
                  "values( :ID_Facture , :ID_Fournisseur_Facture ,:Total_Facture ,  :ID_Produit_Facture ,:Date_Facture ,:Etat_Facture ,:Quantite_Facture )") ;

    query.bindValue(":ID_Facture",res);
    query.bindValue(":ID_Fournisseur_Facture",res2);
    query.bindValue(":Total_Facture",res3);
    query.bindValue(":ID_Produit_Facture",res5);
    query.bindValue(":Date_Facture",datum);
    query.bindValue(":Etat_Facture",Etat_Facture);
    query.bindValue(":Quantite_Facture",res4);

    return query.exec();
}

QSqlQueryModel * Factures::afficher_Facture()
{
    QSqlQueryModel *model = new QSqlQueryModel ;

    model->setQuery("select * from factures") ;
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_Facture"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("ID_Fournisseur_Facture"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Total_Facture"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ID_Produit_Facture"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date_Facture"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Etat_Facture"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Quantite_Facture"));


    return model ;
}

bool Factures::supprimer_Facture(int ID_Facture)
{
    QSqlQuery query ;
    QString res= QString::number(ID_Facture);

    query.prepare("Delete from factures where ID_Facture= :ID_Facture");
    query.bindValue(":ID_Facture",res);

    return query.exec();
}


bool Factures::modifier_Facture(int ID_Facture ,int ID_Fournisseur_Facture ,float Total_Facture,int ID_Produit_Facture,QString Date_Facture,QString Etat_Facture , int Quantite_Facture)
{
    QSqlQuery query ;
    QString res=  QString::number(ID_Facture);
    QString res2= QString::number(ID_Fournisseur_Facture);
    QString res3= QString::number(Total_Facture);
    QString res4= QString::number(Quantite_Facture);
    QString res5= QString::number(ID_Produit_Facture);
    QDate datum = QDate::fromString(Date_Facture,"dd/MM/yyyy");

    query.prepare("UPDATE factures set ID_Fournisseur_Facture=:ID_Fournisseur_Facture,Total_Facture=:Total_Facture,ID_Produit_Facture=:ID_Produit_Facture,Date_Facture=:Date_Facture , Etat_Facture=:Etat_Facture,Quantite_Facture=:Quantite_Facture WHERE ID_Facture=:ID_Facture");

    query.bindValue(":ID_Facture",res);
    query.bindValue(":ID_Fournisseur_Facture",res2);
    query.bindValue(":Total_Facture",res3);
    query.bindValue(":ID_Produit_Facture",res5);
    query.bindValue(":Date_Facture",datum);
    query.bindValue(":Etat_Facture",Etat_Facture);
    query.bindValue(":Quantite_Facture",res4);

    return query.exec();
}


QSqlQueryModel * Factures::Recherche(QString id)
   {
    QSqlQueryModel * model= new QSqlQueryModel();

        QString cherche="Select * from factures where ID_Facture like '"+id+"%' ";
    if (id=="")
    {
        model->setQuery("select * from factures ");
    }
    else
    {
        model->setQuery(cherche);
    }

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_Facture"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("ID_Fournisseur_Facture"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Total_Facture"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ID_Produit_Facture"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date_Facture"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Etat_Facture"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Quantite_Facture"));

        return model;
    }

QSqlQueryModel * Factures::Trier(QString filtre)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    if (filtre=="Voir tout")
    {
        model->setQuery("select * from factures");
    }
    else
    {
        model->setQuery("select * from factures where Etat_Facture like '"+filtre+"' ");
    }
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_Facture"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("ID_Fournisseur_Facture"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Total_Facture"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ID_Produit_Facture"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date_Facture"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Etat_Facture"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Quantite_Facture"));
    return  model;
}

QSqlQueryModel * Factures::Alerte()
{
    QSqlQueryModel *model = new QSqlQueryModel ;

    model->setQuery("select ID_Facture , Total_Facture from factures where Etat_Facture like 'non' ") ;
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_Facture"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Total_Facture"));
    return model ;
}

bool Factures::Alerte2()
{
    int rows ;
    QSqlQuery query;
    bool test =false ;

        query.prepare("Select count(*) from Factures where Etat_Facture like 'non' ");
        query.bindValue(":Etat_Facture", Etat_Facture);
        query.exec();
        rows= 0;
        if (query.next())
         {
            rows= query.value(0).toInt();
         }
         if(rows!=0)
         {
             test=true ;
         }
   return test ;
}





int Factures::Statistiques_Factures_O()
{
    int rows ;
    QSqlQuery query;

        query.prepare("Select count(*) from Factures where Etat_Facture like 'oui' ");
        query.bindValue(":Etat_Facture", Etat_Facture);
        query.exec();
        rows= 0;
        if (query.next())
         {
            rows= query.value(0).toInt();
         }

    return rows;
}

int Factures::Statistiques_Factures_N()
{
    int rows ;
    QSqlQuery query;

        query.prepare("Select count(*) from Factures where Etat_Facture like 'non' ");
        query.bindValue(":Etat_Facture", Etat_Facture);
        query.exec();
        rows= 0;
        if (query.next())
         {
            rows= query.value(0).toInt();
         }

    return rows;
}

int Factures::PK_Check(QString id_Fac)
{
    int rows ;
    QSqlQuery query;

        query.prepare("Select count(*) from Factures where ID_Facture like '"+id_Fac+"' ");
        query.bindValue(":ID_Facture", id_Fac);
        query.exec();
        rows= 0;
        if (query.next())
         {
            rows= query.value(0).toInt();
         }
    return rows;
}

int Factures::FK_Fournisseurs_Check(QString id_fourni)
{
    int rows ;
    QSqlQuery query;

        query.prepare("Select count(*) from Fournisseurs where ID_Fournisseur like '"+id_fourni+"' ");
        query.bindValue(":ID_Fournisseur", id_fourni);
        query.exec();
        rows= 0;
        if (query.next())
         {
            rows= query.value(0).toInt();
         }

    return rows;
}

int Factures::FK_Produits_Check(QString id_prod)
{
    int rows ;
    QSqlQuery query;

        query.prepare("Select count(*) from Produits where ID_Produit like '"+id_prod+"' ");
        query.bindValue(":ID_Produit", id_prod);
        query.exec();
        rows= 0;
        if (query.next())
         {
            rows= query.value(0).toInt();
         }
    return rows;
}

int Factures::Calcul_Total()
{
    int tot ;
    QSqlQuery query;

        query.prepare("Select sum(Total_Facture) from Factures  ");
        query.exec();
        tot= 0;
        if (query.next())
         {
            tot= query.value(0).toInt();
         }


    return tot;
}
