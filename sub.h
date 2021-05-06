#ifndef SUB_H
#define SUB_H
#include<QString>
#include<QDate>
#include <QSqlQueryModel>
#include "qcustomplot.h"


class sub
{
public:
    sub();
    sub(int,QString,QString,QString,int,QDate,QString,QString);
     int getCin();
     int getNum_tel();
     QString getNom();
     QString getPrenom();
     QString getEmail();
     QDate getddn_abonnes();
     QString gettype_abonnement();
     QString getsexe_abonnes();
     void setCin(int);
     void setNum_tel(int);
     void setNom(QString);
     void setPrenom(QString);
     void setEmail(QString);
     void setddn_abonnes(QDate);
     void settype_abonnement(QString);
     void setsexe_abonnes(QString);

     bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();
    bool verifierCin (int);
    bool verifierCin_aj(int);
    bool verifvidestring(QString);
    bool verifint(int);
    bool veriftel(int);
    QSqlQueryModel *afficher_tri_nom ();
    QSqlQueryModel * afficher_tri_prenom ();
    QSqlQueryModel * afficher_tri_ddn ();
    QSqlQueryModel * chercher_abonne(int,QString);
private:
    int Cin;
    QString Nom;
    QString Prenom;
    QString Email;
    int Num_tel;
    QDate ddn_abonnes;
    QString type_abonnement;
    QString sexe;
};

#endif // SUB_H
