#ifndef TICKET_H
#define TICKET_H

#include <QString>
//#include <float.h>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QDate>


class Ticket
{
    int id_ticket , id_evenement , prix;
    QString type_acheteur,type;
    QDate date_achat ;
   // float prix;

public:
    Ticket() ;
    Ticket(int,int,QString,QString,int,QDate);
   // Ticket(int,int,QString,QString,float,QString);
    int getid_ticket () {return id_ticket;}
    int getid_evenement () {return id_evenement;}
    QString gettype_acheteur() {return type_acheteur;}
    QString gettype() {return type;}
    int getprix() {return prix;}
    QDate getdate_achat() {return date_achat;}

    void setid_ticket (int id_ticket){this->id_ticket=id_ticket;}
    void setid_evenement (int id_evenement){this->id_evenement=id_evenement;}
    void settype_acheteur (QString type_acheteur) {this->type_acheteur=type_acheteur ;}
    void settype (QString type) {this->type=type ;}
    void setprix (int prix) {this->prix=prix ;}
    void setdate_achat (QDate date_achat) {this->date_achat=date_achat ;}

  bool ajouter () ;
  QSqlQueryModel* afficher ();

  bool supprimer (int id_ticket);

  QSqlQueryModel * recherche (const QString & aux);
  bool modifier_Ticket(int,int,QString,QString,int,QDate);
  Ticket getTicket(int);
  int calculeTicket(int);
 // bool calculeTicket(int);
  //Ticket getTicket(int);
  QSqlQueryModel * afficher_trie();






private:


};

#endif // TICKET_H
