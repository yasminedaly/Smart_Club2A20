#ifndef FACTURES_H
#define FACTURES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Factures
{
public:
    Factures();
    Factures(int,int,float,QString,QString,QString,QString);
    void Set_ID_Facture(int ID_Facture);
    void Set_ID_Fournisseur_Facture(int ID_Fournisseur_Facture);
    void Set_Total_Facture(float Total_Facture);
    void Set_Nom_Produit_Facture(QString Nom_Produit_Facture);
    void Set_Date_Facture(QString Date_Facture);
    void Set_Etat_Facture(QString Etat_Facture);
    void Set_IMG_Scanee_Facture(QString IMG_Scanee_Facture);

    int Get_ID_Facture() ;
    int Get_ID_Fournisseur_Facture() ;
    float Get_Total_Facture() ;
    QString Get_Nom_Produit_Facture() ;
    QString Get_Date_Facture() ;
    QString Get_Etat_Facture() ;
    QString Get_IMG_Scanee_Facture() ;

    bool ajouter_Facture();
    bool supprimer_Facture(int);
    QSqlQueryModel * afficher_Facture();
    bool modifier_Facture(int,int,float,QString,QString,QString,QString);

private :
    int ID_Facture ;
    int ID_Fournisseur_Facture ;
    float Total_Facture ;
    QString Nom_Produit_Facture ;
    QString Date_Facture ;
    QString Etat_Facture ;
    QString IMG_Scanee_Facture ;
};

#endif // FACTURES_H
