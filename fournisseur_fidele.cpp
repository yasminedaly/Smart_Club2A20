#include "fournisseur_fidele.h"

Fournisseur_Fidele::Fournisseur_Fidele(int ID_Fournisseur , int Nombre_Facture )
{
    this-> ID_Fournisseur = ID_Fournisseur ;
    this-> Nombre_Facture = Nombre_Facture ;
}

Fournisseur_Fidele::Fournisseur_Fidele()
{
    ID_Fournisseur = 0 ;
    Nombre_Facture = 0  ;
}



void Fournisseur_Fidele::Set_ID_Fournisseur(int ID_Fournisseur)
{
    this->ID_Fournisseur=ID_Fournisseur;
}

void Fournisseur_Fidele::Set_Nombre_Facture(int Nombre_Facture)
{
    this->Nombre_Facture=Nombre_Facture;
}



int Fournisseur_Fidele::Get_ID_Fournisseur()
{
    return ID_Fournisseur;
}

int Fournisseur_Fidele::Get_Nombre_Facture()
{
    return Nombre_Facture;
}



bool Fournisseur_Fidele::ajouter_Fournisseur_Fidele()
{
    QSqlQuery query ;
    QString res=  QString::number(ID_Fournisseur);
    QString res2= QString::number(Nombre_Facture);


    query.prepare("insert into Fournisseur_Fidele ( ID_Fournisseur , Nombre_Facture)""values( :ID_Fournisseur , :Nombre_Facture )") ;

    query.bindValue(":ID_Fournisseur",res);
    query.bindValue(":Nombre_Facture",res2);

    return query.exec();
}

QSqlQueryModel * Fournisseur_Fidele::afficher_Fournisseur_Fidele()
{
    QSqlQueryModel *model = new QSqlQueryModel ;

    model->setQuery("select * from Fournisseur_Fidele order by Nombre_Facture DESC ") ;
    //model->setQuery("select * from Fournisseur_Fidele order by Nombre_Facture DESC LIMIT 1") ;

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_Fournisseur"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nombre_Facture"));

    return model ;
}

bool Fournisseur_Fidele::supprimer_Fournisseur_Fidele(int ID_Fournisseur)
{
    QSqlQuery query ;
    QString res= QString::number(ID_Fournisseur);

    query.prepare("Delete from Fournisseur_Fidele where ID_Fournisseur= :ID_Fournisseur");
    query.bindValue(":ID_Fournisseur",res);

    return query.exec();
}

bool Fournisseur_Fidele::modifier_Fournisseur_Fidele(int ID_Fournisseur)
{
    QSqlQuery query ;
    QString res=  QString::number(ID_Fournisseur);



    query.prepare("UPDATE Fournisseur_Fidele SET Nombre_Facture= (Nombre_Facture+1)  where ID_Fournisseur=:ID_Fournisseur") ;

    query.bindValue(":ID_Fournisseur",res);

    return query.exec();
}


bool Fournisseur_Fidele::modifier_Fournisseur_Fidele_decrement(int ID_Fournisseur)
{
    QSqlQuery query ;
    QString res=  QString::number(ID_Fournisseur);



    query.prepare("UPDATE Fournisseur_Fidele SET Nombre_Facture=(Nombre_Facture-1)  where ID_Fournisseur=:ID_Fournisseur") ;

    query.bindValue(":ID_Fournisseur",res);

    return query.exec();
}






