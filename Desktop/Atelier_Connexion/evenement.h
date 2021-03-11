#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>



class Evenement
{
    int id , nb , num;
    QString nom , adresse  , date;

public:
    Evenement() ;
   Evenement(int,QString,QString,int,int,QString);
    int getid () {return id;}
    QString getnom() {return nom;}
    QString getadresse() {return adresse;}
      int getnum () {return num;}
        int getnb () {return nb;}
        QString getdate() {return date;}
    void setid (int id){this->id=id;}
    void setnom (QString nom){this->nom=nom;}
    void setprenom (QString adresse) {this->adresse=adresse ;}
    void setnum (int num){this->num=num;}
    void setnb (int nb){this->nb=nb;}
    void setdate (QString date){this->date=date;}

  bool ajouter () ;
  QSqlQueryModel* afficher ();
  /*
    bool verifierid(int id);
    bool verifvidestring(QString S);
    bool verifint(int S);
    */
  bool supprimer (int id);
  bool  modifier(int id , QString nom, QString adresse , int num , int nb , QString date);
  // bool  modifier(int id , QString nom, int num , int nb , QString date);






private:

};

#endif // EVENEMENT_H
