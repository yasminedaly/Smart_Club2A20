#ifndef HISTORIQUE_H
#define HISTORIQUE_H
#include <QSqlQueryModel>


class Historique
{
public:
    Historique();
    Historique(int,int , int ,int);
    int getid_historique();
    int getelo_max();
    int getnbr_echecs();
    int getnbr_victoires();

    void setid_historique(int);
    void setelo_max(int);
    void setnbr_echecs(int);
    void setnbr_victoires(int);


    bool ajouter_historique();
    QSqlQueryModel * afficher_historique();
    bool verifierid(int);
    bool verifint(int);
    bool supprimer_historique(int);
    bool modifier_historique();

};

#endif // HISTORIQUE_H
