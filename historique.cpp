#include "historique.h"
<<<<<<< HEAD
#include <QSqlQuery>
=======
>>>>>>> 4c29bb4565b29a6c0eaee925a88ecfbd05eec123

Historique::Historique()
{

}
<<<<<<< HEAD
Historique::Historique(int id_joueur,int elo_max , int nbr_echecs , int nbr_victoires)
{
    this->id_joueur=id_joueur;
    this->elo_max=elo_max;
    this->nbr_echecs=nbr_echecs;
    this->nbr_victoires=nbr_victoires;

}


int Historique::getid_joueur(){return id_joueur;}
int Historique::getelo_max(){return elo_max;}
int Historique::getnbr_echecs(){return nbr_echecs;}
int Historique::getnbr_victoires(){return nbr_victoires;}

void Historique::setid_joueur(int id_joueur){this->id_joueur=id_joueur;}
void Historique::setelo_max(int elo_max){this->elo_max=elo_max;}
void Historique::setnbr_echecs(int nbr_echecs){this->nbr_echecs=nbr_echecs;}
void Historique::setnbr_victoires(int nbr_victoires){this->nbr_victoires=nbr_victoires;}

bool Historique::ajouter_historique()
{
    bool test=false;


    QSqlQuery query;
    QString id_string=QString::number(id_joueur);
    QString elo_max_string=QString::number(elo_max);
    QString echecs_string=QString::number(nbr_echecs);
    QString victoires_string=QString::number(nbr_victoires);
    query.prepare("INSERT INTO historiques (id_joueur, elo_max ,  nbr_echecs , nbr_victoires) "
                  "VALUES (:id_joueur, :elo_max ,  :nbr_echecs , :nbr_victoires)");
    query.bindValue(0, id_string);
    query.bindValue(1, elo_max_string);
    query.bindValue(2, echecs_string);
    query.bindValue(3, victoires_string);

    return query.exec();


    return test;
}
=======
>>>>>>> 4c29bb4565b29a6c0eaee925a88ecfbd05eec123
