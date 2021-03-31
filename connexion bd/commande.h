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

class commandeh
{
    int id_commande;
    QString nom_c ;
    QString produit_c;

public:
       commandeh () ;
       commandeh (int,QString,QString) ;
       int getid_commande () {return id_commande;}
       QString get_nom_c(){return nom_c;}
       QString get_produit_c(){return produit_c;}

       void setid (int id_commande){this->id_commande=id_commande;}
       void set_nom_c (QString nom_c) {this->nom_c=nom_c ;}
       void set_nom_produit_c (QString produit_c) {this->produit_c=produit_c ;}




       QSqlQueryModel * afficherhis() ;
       bool ajoutehis();
       bool modifierhis() ;
private:

    //QString cin,datee,fn ;
};

#endif // COMMANDE_H
