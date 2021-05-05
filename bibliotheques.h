#ifndef BIBLIOTHEQUES_H
#define BIBLIOTHEQUES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDialog>
#include<QLabel>



class Bibliotheques
{

    int id_l;
    QString nom_l ;
    QString Ref_livre ;
    QString desc_l ;
    QString date_s ;
    QString date_r ;
    QString displ ;
    QString displ1 ;



public:
    Bibliotheques();
    Bibliotheques(int,QString,QString,QString,QString,QString,QString ,QString );

    int getid_livre () {return id_l ;}
    QString getnom_livre() {return nom_l;}
    QString getref_livre() {return Ref_livre;}
    QString getdesc_livre() {return desc_l;}
    QString getDateS_livre() {return date_s;}
    QString getDateR_livre() {return date_r;}
    QString getdisp_livre() {return displ;}
    QString getdisp1_livre() {return displ1;}



    void setid_livre (int id_l){this->id_l=id_l;}
    void setnom_livre (QString nom_l) {this->nom_l=nom_l ;}
    void setref_livre (QString Ref_livre) {this->Ref_livre=Ref_livre ;}
    void setdesc_livre (QString desc_l) {this->desc_l=desc_l ;}
    void setDateS_livre (QString date_s) {this->date_s=date_s ;}
    void setDateR_livre (QString date_r) {this->date_r=date_r ;}
    void setdisp_livre (QString displ) {this->displ=displ ;}
    void setdisp1_livre (QString displ1) {this->displ1=displ1;}



    bool ajouter_livre () ;
    QSqlQueryModel* afficher_livre ();
    bool supprimer_livre (int);
    bool modifier_livre (int ,QString , QString  , QString ,QString ,QString ,QString ,QString ) ;
    bool rechercher_livre (int);
    QSqlQueryModel * tri_livre () ;
    QSqlQueryModel * tri2 (QString);

    QSqlQueryModel * chercher_matpar_ref(QString  Ref_livre);
    QSqlQueryModel * chercher_matpar_nom(QString  nom_l);


    bool controlSaisieCharVide (QString,QString);
    bool controlsaisieRef(QString saisi);





};

#endif // BIBLIOTHEQUES_H
