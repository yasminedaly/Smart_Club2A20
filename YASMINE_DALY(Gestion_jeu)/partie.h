#ifndef PARTIE_H
#define PARTIE_H
#include <QString>
#include <QSqlQueryModel>

class Partie
{
public:
    Partie();
    Partie(int,QString,int,int,QString,QString,QString,int,QString);

    int getid_partie();
    QString getcadence();
    int getid_noir();
    int getid_blanc();
    QString getdebut_partie();
    QString getfin_partie();
    QString getgagnant_partie();
    int getnum_table();
    QString getcom_partie();

    void setid_partie(int);
    void setcadence(QString);
    void setid_noir(int);
    void setid_blanc(int);
    void setdebut_partie(QString);
    void setfin_partie(QString);
    void setgagnant_partie(QString);
    void setnum_table(int);
    void setcom_partie(QString);

    bool ajouter_partie();
    bool verifierid_aj(int);
    bool verifierid(int);
    bool verifvidestring(QString);
    bool verifint(int);
    QSqlQueryModel * afficher_partie();
    bool supprimer_partie(int);
    bool modifier_partie();
    QSqlQueryModel* chercher_partie(int,QString);
    QSqlQueryModel* trier_partie(int);


private:
    int id_partie;
    QString cadence;
    int id_noir;
    int id_blanc;
    QString debut_partie;
    QString fin_partie;
    QString gagnant_partie;
    int num_table;
    QString com_partie;
};

#endif // PARTIE_H
