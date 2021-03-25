#ifndef FACTURES_H
#define FACTURES_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QDate>

class Factures
{
public:
    Factures();
    Factures(int,int,float,int,QString,QString,int);



    void Set_ID_Facture(int ID_Facture);
    void Set_ID_Fournisseur_Facture(int ID_Fournisseur_Facture);
    void Set_Total_Facture(float Total_Facture);
    void Set_Nom_Produit_Facture(int Nom_Produit_Facture);
    void Set_Date_Facture(QString Date_Facture);
    void Set_Etat_Facture(QString Etat_Facture);
    void Set_Quantite_Facture(int Quantite_Facture);


    int Get_ID_Facture() ;
    int Get_ID_Fournisseur_Facture() ;
    float Get_Total_Facture() ;
    int Get_Nom_Produit_Facture() ;
    QString Get_Date_Facture() ;
    QString Get_Etat_Facture() ;
    int Get_Quantite_Facture();


    bool ajouter_Facture();
    bool supprimer_Facture(int);
    QSqlQueryModel * afficher_Facture();
    bool modifier_Facture(int,int,float,int,QString,QString,int);



private :
    int ID_Facture ;
    int ID_Fournisseur_Facture ;
    float Total_Facture ;
    int Quantite_Facture ;
    int Nom_Produit_Facture ;
    QString Date_Facture ;
    QString Etat_Facture ;
};

#endif // FACTURES_H
