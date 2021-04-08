#ifndef HISTORIQUE_H
#define HISTORIQUE_H
#include <QSqlQueryModel>


class Historique
{
public:
    Historique();
    Historique(int,int , int ,int);
<<<<<<< HEAD
    int getid_joueur();
=======
    int getid_historique();
>>>>>>> 4c29bb4565b29a6c0eaee925a88ecfbd05eec123
    int getelo_max();
    int getnbr_echecs();
    int getnbr_victoires();

<<<<<<< HEAD
    void setid_joueur(int);
=======
    void setid_historique(int);
>>>>>>> 4c29bb4565b29a6c0eaee925a88ecfbd05eec123
    void setelo_max(int);
    void setnbr_echecs(int);
    void setnbr_victoires(int);


    bool ajouter_historique();
    QSqlQueryModel * afficher_historique();
    bool verifierid(int);
    bool verifint(int);
<<<<<<< HEAD
    bool modifier_historique();

private:
    int id_joueur;
    int elo_max;
    int nbr_echecs;
    int nbr_victoires;

=======
    bool supprimer_historique(int);
    bool modifier_historique();

>>>>>>> 4c29bb4565b29a6c0eaee925a88ecfbd05eec123
};

#endif // HISTORIQUE_H
