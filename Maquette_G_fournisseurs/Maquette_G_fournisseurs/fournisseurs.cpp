#include "fournisseurs.h"

Fournisseurs::Fournisseurs(int ID_Fournisseur , QString Nom_Fournisseur , QString Adresse_Fournisseur , int Telephone_Fournisseur, QString Email_Fournisseur )
{
    this-> ID_Fournisseur = ID_Fournisseur ;
    this-> Nom_Fournisseur = Nom_Fournisseur ;
    this-> Adresse_Fournisseur = Adresse_Fournisseur ;
    this-> Telephone_Fournisseur = Telephone_Fournisseur ;
    this-> Email_Fournisseur = Email_Fournisseur ;
}

Fournisseurs::Fournisseurs()
{

}


void Fournisseurs::Set_ID_Fournisseur(int ID_Fournisseur)
{
    this->ID_Fournisseur=ID_Fournisseur;
}

void Fournisseurs::Set_Nom_Fournisseur(QString Nom_Fournisseur)
{
    this->Nom_Fournisseur=Nom_Fournisseur;
}

void Fournisseurs::Set_Adresse_Fournisseur(QString Adresse_Fournisseur)
{
    this->Adresse_Fournisseur=Adresse_Fournisseur;
}

void Fournisseurs::Set_Telephone_Fournisseur(int Telephone_Fournisseur)
{
    this->Telephone_Fournisseur=Telephone_Fournisseur;
}

void Fournisseurs::Set_Email_Fournisseur(QString Email_Fournisseur)
{
    this->Email_Fournisseur=Email_Fournisseur;
}


int Fournisseurs::Get_ID_Fournisseur()
{
    return ID_Fournisseur;
}

QString Fournisseurs::Get_Nom_Fournisseur()
{
    return Nom_Fournisseur;
}

QString Fournisseurs::Get_Adresse_Fournisseur()
{
    return Adresse_Fournisseur;
}

int Fournisseurs::Get_Telephone_Fournisseur()
{
    return Telephone_Fournisseur;
}

QString Fournisseurs::Get_Email_Fournisseur()
{
    return Email_Fournisseur;
}


bool Fournisseurs::ajouter_Fournisseur()
{
    QSqlQuery query ;
    QString res=  QString::number(ID_Fournisseur);
    QString res2= QString::number(Telephone_Fournisseur);

    query.prepare("insert into fournisseurs ( ID_Fournisseur , Nom_Fournisseur , Adresse_Fournisseur , Telephone_Fournisseur, Email_Fournisseur )""values( :ID_Fournisseur , :Nom_Fournisseur , :Adresse_Fournisseur , :Telephone_Fournisseur, :Email_Fournisseur )") ;

    query.bindValue(":ID_Fournisseur",res);
    query.bindValue(":Nom_Fournisseur",Nom_Fournisseur);
    query.bindValue(":Adresse_Fournisseur",Adresse_Fournisseur);
    query.bindValue(":Telephone_Fournisseur",res2);
    query.bindValue(":Email_Fournisseur",Email_Fournisseur);

    return query.exec();
}

QSqlQueryModel * Fournisseurs::afficher_Fournisseur()
{
    QSqlQueryModel *model = new QSqlQueryModel ;

    model->setQuery("select * from fournisseurs") ;
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_Fournisseur"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom_Fournisseur"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Adresse_Fournisseur"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Telephone_Fournisseur"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Email_Fournisseur"));

    return model ;
}

bool Fournisseurs::supprimer_Fournisseur(int ID_Fournisseur)
{
    QSqlQuery query ;
    QString res= QString::number(ID_Fournisseur);

    query.prepare("Delete from fournisseurs where ID_Fournisseur= :ID_Fournisseur");
    query.bindValue(":ID_Fournisseur",res);

    return query.exec();
}

bool Fournisseurs::modifier_Fournisseur(int ID_Fournisseur , QString Nom_Fournisseur , QString Adresse_Fournisseur , int Telephone_Fournisseur, QString Email_Fournisseur )
{
    QSqlQuery query ;
    QString res=  QString::number(ID_Fournisseur);
    QString res2= QString::number(Telephone_Fournisseur);



    query.prepare("UPDATE fournisseurs SET Nom_Fournisseur='"+Nom_Fournisseur+"' , Adresse_Fournisseur='"+Adresse_Fournisseur+"' , Telephone_Fournisseur ='"+res2+"', Email_Fournisseur ='"+Email_Fournisseur+"' where ID_Fournisseur=:ID_Fournisseur") ;

    query.bindValue(":ID_Fournisseur",res);
    query.bindValue(":Nom_Fournisseur",Nom_Fournisseur);
    query.bindValue(":Adresse_Fournisseur",Adresse_Fournisseur);
    query.bindValue(":Telephone_Fournisseur",res2);
    query.bindValue(":Email_Fournisseur",Email_Fournisseur);

    return query.exec();
}


QSqlQueryModel * Fournisseurs::Recherche(QString id)
   {
    QSqlQueryModel * model= new QSqlQueryModel();

    QString model="Select * from fournisseurs where ID_Fournisseur like '"+id+"%' ";

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_Fournisseur"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom_Fournisseur"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse_Fournisseur"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Telephone_Fournisseur"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Email_Fournisseur"));

        return model;
    }

QSqlQueryModel * Fournisseurs::Trier()
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from fournisseurs order by ID_Fournisseur desc");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_Fournisseur"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom_Fournisseur"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse_Fournisseur"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Telephone_Fournisseur"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Email_Fournisseur"));
    return  model;
}
