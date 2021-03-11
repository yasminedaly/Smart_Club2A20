#include "factures.h"
#include <QSqlQuery>
#include <QSqlQueryModel>

Factures::Factures()
{

}

Factures::Factures(int ID_Facture,int ID_Fournisseur_Facture,float Total_Facture ,QString Nom_Produit_Facture,QString Date_Facture,QString Etat_Facture,QString IMG_Scanee_Facture)
{
    this->ID_Facture = ID_Facture ;
    this->ID_Fournisseur_Facture = ID_Fournisseur_Facture ;
    this->Total_Facture = Total_Facture ;
    this->Nom_Produit_Facture = Nom_Produit_Facture ;
    this->Date_Facture = Date_Facture ;
    this->Etat_Facture = Etat_Facture ;
    this->IMG_Scanee_Facture = IMG_Scanee_Facture ;
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



void Factures::Set_Nom_Produit_Facture(QString Nom_Produit_Facture)
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

void Factures::Set_IMG_Scanee_Facture(QString IMG_Scanee_Facture)
{
    this->IMG_Scanee_Facture=IMG_Scanee_Facture;
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



QString Factures::Get_Nom_Produit_Facture()
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

QString Factures::Get_IMG_Scanee_Facture()
{
    return IMG_Scanee_Facture;
}



bool Factures::ajouter_Facture()
{
    QSqlQuery query ;
    QString res=  QString::number(ID_Facture);
    QString res2= QString::number(ID_Fournisseur_Facture);
    QString res3= QString::number(Total_Facture);

    query.prepare("insert into factures (ID_Facture,ID_Fournisseur_Facture,Total_Facture,Nom_Produit_Facture,Date_Facture,Etat_Facture,IMG_Scanee_Facture)""values( :ID_Facture , :ID_Fournisseur_Facture ,:Total_Facture ,  :Nom_Produit_Facture ,:Date_Facture ,:Etat_Facture ,:IMG_Scanee_Facture)") ;

    query.bindValue(":ID_Facture",res);
    query.bindValue(":ID_Fournisseur_Facture",res2);
    query.bindValue(":Total_Facture",res3);
    query.bindValue(":Nom_Produit_Facture",Nom_Produit_Facture);
    query.bindValue(":Date_Facture",Date_Facture);
    query.bindValue(":Etat_Facture",Etat_Facture);
    query.bindValue(":IMG_Scanee_Facture",IMG_Scanee_Facture);

    return query.exec();
}
QSqlQueryModel * Factures::afficher_Facture()
{
    QSqlQueryModel *model = new QSqlQueryModel ;

    model->setQuery("select * from factures") ;
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_Facture"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("ID_Fournisseur_Facture"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Total_Facture"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Nom_Produit_Facture"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Date_Facture"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Etat_Facture"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IMG_Scanee_Facture"));

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


bool Factures::modifier_Facture(int ID_Facture ,int ID_Fournisseur_Facture ,float Total_Facture,QString Nom_Produit_Facture,QString Date_Facture,QString Etat_Facture,QString IMG_Scanee_Facture)
{
    QSqlQuery query ;
    QString res=  QString::number(ID_Facture);
    QString res2= QString::number(ID_Fournisseur_Facture);
    QString res3= QString::number(Total_Facture);

    query.prepare(" UPDATE factures SET ID_Facture='"+res+"' , ID_Fournisseur_Facture='"+res2+"',Total_Facture='"+res3+"',Nom_Produit_Facture='"+Nom_Produit_Facture+"',Date_Facture='"+Date_Facture+"',Etat_Facture='"+Etat_Facture+"',IMG_Scanee_Facture='"+IMG_Scanee_Facture+"' where ID_Facture=:ID_Facture ") ;

    query.bindValue(":ID_Facture",res);
    query.bindValue(":ID_Fournisseur_Facture",res2);
    query.bindValue(":Total_Facture",res3);
    query.bindValue(":Nom_Produit_Facture",Nom_Produit_Facture);
    query.bindValue(":Date_Facture",Date_Facture);
    query.bindValue(":Etat_Facture",Etat_Facture);
    query.bindValue(":IMG_Scanee_Facture",IMG_Scanee_Facture);

    return query.exec();
}


