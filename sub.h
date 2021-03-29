#ifndef SUB_H
#define SUB_H
#include<QString>
#include<QDate>
#include <QSqlQueryModel>


class sub
{
public:
    sub();
    sub(int,QString,QString,QString,int,QDate,QString);
     int getCin();
     int getNum_tel();
     QString getNom();
     QString getPrenom();
     QString getEmail();
     QDate getddn_abonnes();
     QString gettype_abonnement();
     void setCin(int);
     void setNum_tel(int);
     void setNom(QString);
     void setPrenom(QString);
     void setEmail(QString);
     void setddn_abonnes(QDate);
     void settype_abonnement(QString);
     bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();
    bool verifierCin(int);
private:
    int Cin;
    QString Nom;
    QString Prenom;
    QString Email;
    int Num_tel;
    QDate ddn_abonnes;
    QString type_abonnement;
};

#endif // SUB_H
