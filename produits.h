#ifndef PRODUITS_H
#define PRODUITS_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Produits
{
public :
    Produits();
    Produits(int , QString , int , float);
    void Set_iD_Produit(int ID_Produit);
    void Set_Nom_Produit(QString Nom_Produit);
    void Set_Quantite_Produit(int Quantite_Produit);
    void Set_Prix_Produit(float Prix_Produit);


    int Get_ID_Produit() ;
    QString Get_Nom_Produit() ;
    int Get_Quantite_Produit() ;
    float Get_Prix_Produit() ;


    bool Verifier_ID(int);
    bool Verifier_QString_Vide(QString);
    bool Verifier_Int(int);

    bool incrementer_nbr(int ID_Produit , int Quantite_Produit ) ;
    bool ajouter_Produit();
    bool supprimer_Produit(int);
    QSqlQueryModel * afficher_Produit();
    bool modifier_Produit(int , QString , int , float);

    int PK_Check(QString id_Prod);

    QSqlQueryModel * Recherche_ID(QString id);
    QSqlQueryModel * Recherche_Nom(QString Nom);
    QSqlQueryModel * Recherche_Quantite(QString Quantite);
    QSqlQueryModel * Recherche_Prix(QString Prix);
    QSqlQueryModel * trier() ;
    QStringList listeProduits();


private :
    int ID_Produit ;
    QString Nom_Produit ;
    int Quantite_Produit ;
    float Prix_Produit ;

};

#endif // PRODUITS_H
