#ifndef ETUDIANT_H
#define ETUDIANT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>



class Etudiant
{
    int id;
    QString nom , prenom ;

public:
    Etudiant() ;
    Etudiant(int,QString,QString);
    int getid () {return id;}
    QString getnom() {return nom;}
    QString getprenom() {return prenom;}
    void setid (int id){this->id=id;}
    void setnom (QString nom){this->nom=nom;}
    void setprenom (QString prenom) {this->prenom=prenom ;}

  bool ajouter () ;
  QSqlQueryModel* afficher ();

  bool supprimer (int id);






private:
    /*int id;
    QString nom , prenom ;*/

};

#endif // ETUDIANT_H
