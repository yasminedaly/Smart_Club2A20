#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QDate>

// Yosra

class Evenement
{
    int id , nb , num;
    QString nom , adresse  ;
    QDate date;

public:
    Evenement() ;
   Evenement(int,QString,QString,int,int,QDate);
    int getid () {return id;}
    QString getnom() {return nom;}
    QString getadresse() {return adresse;}
      int getnum () {return num;}
        int getnb () {return nb;}
        QDate getdate() {return date;}
    void setid (int id){this->id=id;}
    void setnom (QString nom){this->nom=nom;}
    void setadresse (QString adresse) {this->adresse=adresse ;}
    void setnum (int num){this->num=num;}
    void setnb (int nb){this->nb=nb;}
    void setdate (QDate date){this->date=date;}


  bool ajouter () ;
  QSqlQueryModel* afficher ();

  bool supprimer (int id);
  bool modifier(int,QString,QString,int,int,QDate);


  QSqlQueryModel * recherche (const QString & aux);

  QSqlQueryModel * afficher_trie();
  Evenement getEvenement(int);
  QStringList listeEvents();











private:

};

#endif // EVENEMENT_H
