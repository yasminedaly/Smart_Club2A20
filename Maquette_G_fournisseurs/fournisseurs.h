#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Fournisseurs
{
public:
    Fournisseurs();
    Fournisseurs(int,QString,QString,int,QString);


    void Set_ID_Fournisseur(int ID_Fournisseur);
    void Set_Nom_Fournisseur(QString Nom_Fournisseur);
    void Set_Adresse_Fournisseur(QString Adresse_Fournisseur);
    void Set_Telephone_Fournisseur(int Telephone_Fournisseur);
    void Set_Email_Fournisseur(QString Email_Fournisseur);



    int Get_ID_Fournisseur() ;
    QString Get_Nom_Fournisseur() ;
    QString Get_Adresse_Fournisseur() ;
    int Get_Telephone_Fournisseur() ;
    QString Get_Email_Fournisseur() ;


    bool ajouter_Fournisseur();
    bool supprimer_Fournisseur(int);
    QSqlQueryModel * afficher_Fournisseur();
    bool modifier_Fournisseur(int,QString,QString,int,QString);
    QSqlQueryModel * Recherche(QString) ;
    QSqlQueryModel * Trier();



private :
    int ID_Fournisseur ;
    QString Nom_Fournisseur ;
    QString Adresse_Fournisseur ;
    int Telephone_Fournisseur ;
    QString Email_Fournisseur ;

};

#endif // FOURNISSEURS_H
