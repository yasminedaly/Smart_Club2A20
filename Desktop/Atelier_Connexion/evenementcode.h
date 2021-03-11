#ifndef EVENEMENT_H
#define EVENEMENT_H
#include <QString>
#include <QMainWindow>
#include <QObject>
#include <QSharedDataPointer>
#include <QWidget>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QDate>

class EVENEMENT
{
private:
    QString nom_event , adresse_event,photo_event;
    int id_event , num_tel,nb_participants;
    QDate date_event;
public:
    //constructeurs
    EVENEMENT();
    EVENEMENT(int,QString,QString,int,int,QDate,QString);

    // getters
    int getid_event();
    QString getnom_event();
    QString getadresse_event();
    int getnum_tel();
    int getnb_participants();
     QDate getdate_event();
    QString getphoto_event();


    //setters
    void setid_event(int );
    void setnom_event(QString );
    void setadresse_event(QString );
    void setnum_tel(int );
    void setnb_participants(int );
    void setdate_event(QDate );
    void setphoto_event(QString );


    //fonctions de base relative a l'entite evenement
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);

  };

#endif
