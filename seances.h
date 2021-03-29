#ifndef SEANCES_H
#define SEANCES_H
#include<QString>
#include <QSqlQueryModel>
#include<QDate>


class seances
{
public:
    seances();
    seances(int,int,int,int,QString,QDate,QString);
    int getID_salle();
    int getID_employe();
    int getNum_salle();
    int getCapacite_salle();
    QString getTitre_cours();
    QDate getDate_seance();
    QString getNiveau_seance();
    void setID_salle(int);
    void setID_employe(int);
    void setNum_salle(int);
    void setCapacite_salle(int);
    void setTitre_cours(QString);
    void setDate_seance(QDate);
    void setNiveau_seance(QString);
    bool ajouter_S();
    QSqlQueryModel* afficher_S();
    bool modifier_S();
    bool supprimer_S(int);


private:
    int ID_salle;
    int Num_salle ;
    int ID_employe ;
    int Capacite_salle;
    QString Titre_cours;
    QDate Date_seance;
    QString Niveau_seance;
};

#endif // SEANCES_H
