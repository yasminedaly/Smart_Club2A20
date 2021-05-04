#ifndef CONGE_H
#define CONGE_H
#include <QString>
#include "qstring.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>

class conge
{
public:
    conge();
    conge(QString i,QString n,QString dd,QString df,QString t):id(i),nom(n),dated(dd),datef(df),type(t){}
    void setid(QString n);
    void setnom(QString n);
    void setdated(QString n);
    void setdatef(QString n);
    void settype(QString n);
    QString get_id();
    QString get_nom();
    QString get_dated();
    QString get_datef();
    QString get_type();
    bool ajouter();
    bool supprimer(QString idconge);
    QSqlQueryModel *afficher();
    QSqlQueryModel *recherche(QString);
    QSqlQueryModel *rechercher_type(QString);
    QSqlQueryModel *rechercher_nomemploye(QString);
    QSqlQueryModel *rechercher_combinaison_all(QString,QString,QString);
    QSqlQueryModel *rechercher_combinaison_id_nom(QString,QString);
    QSqlQueryModel *rechercher_combinaison_id_type(QString,QString);
    QSqlQueryModel *rechercher_combinaison_nom_type(QString,QString);
private:
    QString id;
    QString nom;
    QString dated;
    QString datef;
    QString type;
};

#endif // CONGE_H
