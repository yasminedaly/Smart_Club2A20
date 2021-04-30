#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Fournisseurs
{
public:
    Fournisseurs();
    Fournisseurs(int,QString,QString,QString,QString);
    void Set_ID_Fournisseur(int ID_Fournisseur);
    void Set_Nom_Fournisseur(QString Nom_Fournisseur);
    void Set_Adresse_Fournisseur(QString Adresse_Fournisseur);
    void Set_Telephone_Fournisseur(QString Telephone_Fournisseur);
    void Set_Email_Fournisseur(QString Email_Fournisseur);

    int Get_ID_Fournisseur() ;
    QString Get_Nom_Fournisseur() ;
    QString Get_Adresse_Fournisseur() ;
    QString Get_Telephone_Fournisseur() ;
    QString Get_Email_Fournisseur() ;

    int PK_Check(QString id_Fac);

    bool Verifier_ID(int);
    bool Verifier_QString_Vide(QString);
    bool Verifier_INT(int);



    bool ajouter_Fournisseur();
    bool supprimer_Fournisseur(int);
    QSqlQueryModel * afficher_Fournisseur();
    bool modifier_Fournisseur(int,QString,QString,QString,QString);


    QSqlQueryModel * Recherche(QString) ;
    QSqlQueryModel * Trier(QString);
    QStringList listeFournisseurs();



private :
    int ID_Fournisseur ;
    QString Nom_Fournisseur ;
    QString Adresse_Fournisseur ;
    QString Telephone_Fournisseur ;
    QString Email_Fournisseur ;

};

#endif // FOURNISSEURS_H
