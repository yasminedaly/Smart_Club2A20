#ifndef COMMANDE_H
#define COMMANDE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>



class commande
{
    int id_commande;
    int nb_produit ;
    float Prix_t ;
    QString Date_commande ;


public:
    commande() ;
   commande(int,int,float,QString);

    int getid_commande () {return id_commande;}
    int getnb_produit () {return nb_produit;}
    float getprix () {return Prix_t;}
    QString getDate_commande() {return Date_commande;}

    void setid (int id_commande){this->id_commande=id_commande;}
    void setnb_produit (int nb_produit){this->nb_produit=nb_produit;}
    void setPrix_t (float Prix_t){this->Prix_t=Prix_t;}
    void setDate (QString Date_commande) {this->Date_commande=Date_commande ;}

  bool ajouter () ;
  QSqlQueryModel* afficher ();
  QSqlQueryModel * tri() ;
  //QSqlQueryModel * recherche(int id_commandeA);


  bool supprimer (int);
  bool modifier (int ,int , float , QString ) ;
 bool rechercher(int);






private:
    /*int id;
    QString nom , prenom ;*/


};

#endif // COMMANDE_H
