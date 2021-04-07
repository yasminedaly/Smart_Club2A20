#include "factures.h"
#include <QSqlQuery>
#include <QSqlQueryModel>

Factures::Factures()
{

}

Factures::Factures(int ID_Facture,int ID_Fournisseur_Facture,float Total_Facture ,int Nom_Produit_Facture,QString Date_Facture,QString Etat_Facture , int Quantite_Facture)
{
    this->ID_Facture = ID_Facture ;
    this->ID_Fournisseur_Facture = ID_Fournisseur_Facture ;
    this->Total_Facture = Total_Facture ;
    this->Nom_Produit_Facture = Nom_Produit_Facture ;
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



void Factures::Set_Nom_Produit_Facture(int Nom_Produit_Facture)
{
    this->Nom_Produit_Facture=Nom_Produit_Facture;
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


int Factures::Get_Nom_Produit_Facture()
{
    return Nom_Produit_Facture;
}

QString Factures::Get_Date_Facture()
{
    return Date_Facture;
}

QString Factures::Get_Etat_Facture()
{
    return Etat_Facture;
}


bool Factures::ajouter_Facture()
{
    QSqlQuery query ;
    QString res=  QString::number(ID_Facture);
    QString res2= QString::number(ID_Fournisseur_Facture);
    QString res3= QString::number(Total_Facture);
    QString res4= QString::number(Quantite_Facture);
    QString res5= QString::number(Nom_Produit_Facture);

    query.prepare("insert into factures (ID_Facture,ID_Fournisseur_Facture,Total_Facture,Nom_Produit_Facture,Date_Facture,Etat_Facture,Quantite_Facture)""" "values( :ID_Facture , :ID_Fournisseur_Facture ,:Total_Facture ,  :Nom_Produit_Facture ,:Date_Facture ,:Etat_Facture ,:Quantite_Facture )") ;

    query.bindValue(":ID_Facture",res);
    query.bindValue(":ID_Fournisseur_Facture",res2);
    query.bindValue(":Total_Facture",res3);
    query.bindValue(":Nom_Produit_Facture",res5);
    query.bindValue(":Date_Facture",Date_Facture);
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
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Nom_Produit_Facture"));
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


bool Factures::modifier_Facture(int ID_Facture ,int ID_Fournisseur_Facture ,float Total_Facture,int Nom_Produit_Facture,QString Date_Facture,QString Etat_Facture , int Quantite_Facture)
{
    QSqlQuery query ;
    QString res=  QString::number(ID_Facture);
    QString res2= QString::number(ID_Fournisseur_Facture);
    QString res3= QString::number(Total_Facture);
    QString res4= QString::number(Quantite_Facture);
    QString res5= QString::number(Nom_Produit_Facture);

    query.prepare("UPDATE factures set ID_Fournisseur_Facture=:ID_Fournisseur_Facture,Total_Facture=:Total_Facture,Nom_Produit_Facture=:Nom_Produit_Facture,Date_Facture=:Date_Facture , Etat_Facture=:Etat_Facture,Quantite_Facture=:Quantite_Facture WHERE ID_Facture=:ID_Facture");

    query.bindValue(":ID_Facture",res);
    query.bindValue(":ID_Fournisseur_Facture",res2);
    query.bindValue(":Total_Facture",res3);
    query.bindValue(":Nom_Produit_Facture",res5);
    query.bindValue(":Date_Facture",Date_Facture);
    query.bindValue(":Etat_Facture",Etat_Facture);
    query.bindValue(":Quantite_Facture",res4);

    return query.exec();
}

QSqlQueryModel * Factures::Trier()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from factures where Etat_Facture order by ID_Facture  ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_Facture"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("ID_Fournisseur_Facture"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Total_Facture"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Nom_Produit_Facture"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date_Facture"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Etat_Facture"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Quantite_Facture"));
    return  model;
}

QSqlQueryModel * Factures::Recherche(QString id)
   {
    QSqlQueryModel * model= new QSqlQueryModel();

     model->setQuery("select * from factures ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_Facture"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("ID_Fournisseur_Facture"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Total_Facture"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ID_Produit_Facture"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date_Facture"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Etat_Facture"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Quantite_Facture"));

        return model;
    }



