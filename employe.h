#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>
#include <QDate>
class employe
{
public:
    employe();
    employe(QString i,QString n,QString nu, QString m,QString d,QString s, QString dep, QString sa):id(i),nom(n),num(nu),mail(m),datead(d),sexe(s),departement(dep),salaire(sa){}
    //CRUD
    bool ajouter();
    bool supprimer(QString idemploye);
    QSqlQueryModel *afficher();
    //metiers
    QSqlQueryModel *recherche(QString);
    QSqlQueryModel *trier(QString,QString);
    QSqlQueryModel *rechercher_cin(QString);
    QSqlQueryModel *rechercher_nom(QString);
    QSqlQueryModel *rechercher_sexe(QString);
    QSqlQueryModel *rechercher_date(QDate);
    QSqlQueryModel *rechercher_email(QString);
    QSqlQueryModel *rechercher_combinaison_all(QString,QString,QDate);
    QSqlQueryModel *rechercher_combinaison_nom_date(QString,QDate);
    QSqlQueryModel *rechercher_combinaison_sexe_date(QString,QDate);
    QSqlQueryModel *rechercher_combinaison_nom_sexe(QString,QString);
    void sendMail( const QString &from, const QString &to, const QString &subject, const QString &body );


    int stati();
    int stati1();
    int stati2();
    int nb_total();


private:
    QString id;
    QString nom;
    QString num;
    QString mail;
    QString datead;
    QString sexe;
    QString departement;
    QString salaire;

};
#endif // EMPLOYE_H
