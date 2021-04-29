#ifndef JOUEUR_H
#define JOUEUR_H
#include <QString>
#include <QSqlQueryModel>
#include <QPdfWriter>
#include <QBuffer>
#include <cstdlib>
#include <QImage>


class Joueur
{
public:
    Joueur();
    Joueur(int,QString , QString ,QString , QString ,QString , int , int );
    int getid_joueur();
    QString getnom_joueur();
    QString getprenom_joueur();
    QString getville_joueur();
    QString getdn_joueur();
    QString getemail_joueur();
    int gettel_joueur();
    int getclassement_elo();
    QByteArray  getphoto_joueur() ;
    void  AjoutImage(QString );


    void setid_joueur(int);
    void setnom_joueur(QString);
    void setprenom_joueur(QString);
    void setville_joueur(QString);
    void setdn_joueur(QString);
    void setemail_joueur(QString);
    void settel_joueur(int);
    void setclassement_elo(int);
    void setphoto_joueur(QByteArray);
    bool ajouter_joueur();
    QSqlQueryModel * afficher_joueur();
    bool verifierid(int);
    bool verifierid_aj(int);
    bool verifvidestring(QString);
    bool verifint(int);
    bool veriftel(int);
    bool supprimer_joueur(int);
    bool modifier_joueur();
    QSqlQueryModel* chercher_joueur(int,QString);
    QSqlQueryModel* trier_joueur(int);


private:
    int id_joueur;
    QString nom_joueur;
    QString prenom_joueur;
    QString ville_joueur;
    QString dn_joueur;
    QString email_joueur;
    int tel_joueur;
    int classement_elo;
    QByteArray photo_joueur;

};

#endif // JOUEUR_H
