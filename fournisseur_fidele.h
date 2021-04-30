#ifndef FOURNISSEUR_FIDELE_H
#define FOURNISSEUR_FIDELE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Fournisseur_Fidele
{
public:
    Fournisseur_Fidele();
    Fournisseur_Fidele(int,int);
    void Set_ID_Fournisseur(int ID_Fournisseur);
    void Set_Nombre_Facture(int Nombre_Facture);

    int Get_ID_Fournisseur();
    int Get_Nombre_Facture();

    bool ajouter_Fournisseur_Fidele();
    bool supprimer_Fournisseur_Fidele(int);
    QSqlQueryModel * afficher_Fournisseur_Fidele();
    bool modifier_Fournisseur_Fidele(int);
    bool modifier_Fournisseur_Fidele_decrement(int);

private :
    int ID_Fournisseur ;
    int Nombre_Facture ;
};

#endif // FOURNISSEUR_FIDELE_H
