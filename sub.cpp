#include "sub.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <QObject>
#include <QDate>
sub::sub()
{
 Cin=0;Num_tel=0; Nom=""; Prenom="" ;Email="";ddn_abonnes=QDate::currentDate();type_abonnement="";sexe="";
}
sub::sub(int Cin,QString Email,QString Nom,QString Prenom,int Num_tel,QDate ddn_abonnes,QString type_abonnement,QString sexe)
{this->Cin=Cin; this->Num_tel=Num_tel; this->Nom=Nom; this->Prenom=Prenom;this->Email=Email;this->ddn_abonnes=ddn_abonnes;this->type_abonnement=type_abonnement;this->sexe=sexe;}
int sub::getCin(){return Cin;}
int sub::getNum_tel(){return Num_tel;}
 QString sub::getNom(){return Nom;}
 QString sub::getPrenom(){return Prenom;}
 QString sub::getEmail(){return Email;}
 QDate sub::getddn_abonnes(){return ddn_abonnes;}
 QString sub::gettype_abonnement(){return type_abonnement;}
 QString sub::getsexe_abonnes(){return sexe;}
 void sub::setCin(int Cin){this->Cin=Cin;}
 void sub::setNum_tel(int Num_tel){this->Num_tel=Num_tel;}
 void sub::setNom(QString Nom){this->Nom=Nom;}
 void sub::setPrenom(QString Prenom){this->Prenom=Prenom;}
 void sub::setEmail(QString Email){this->Email=Email;}
 void sub::setddn_abonnes(QDate ddn_abonnes){this->ddn_abonnes=ddn_abonnes;}
 void sub::settype_abonnement(QString type_abonnement){this->type_abonnement=type_abonnement;}
 void sub::setsexe_abonnes(QString sexe){this->sexe=sexe;}
 bool sub::ajouter()
 {
     bool test=false;
     QSqlQuery query;
     QString Cin_string= QString::number(Cin);
     QString TEL_string= QString::number(Num_tel);
       query.prepare("INSERT INTO abonnes (cin_abonnes, email_abonnes, nom_abonnes,prenom_abonnes,tel_abonnes,ddn_abonnes,type_abonnement,sexe) "
                     "VALUES (:cin_abonnes, :email_abonnes, :nom_abonnes,:prenom_abonnes,:tel_abonnes,:ddn_abonnes,:type_abonnement,:sexe)");
       query.bindValue(0,Cin_string);
       query.bindValue(1,Email);
       query.bindValue(2, Nom);
       query.bindValue(3, Prenom);
       query.bindValue(4, TEL_string);
       query.bindValue(5, ddn_abonnes);
       query.bindValue(6, type_abonnement);
       query.bindValue(7,sexe);
       query.exec();
       test =true;
     return test ;
 }
 bool sub::supprimer(int Cin){

    QSqlQuery query;
      QString res=QString::number(Cin);
      query.prepare("Delete from abonnes where cin_abonnes = :cin_abonnes ");
      query.bindValue(":cin_abonnes",res); //affectation et association des val
      return query.exec();

 }
 QSqlQueryModel* sub::afficher()
 {
      QSqlQueryModel* model=new  QSqlQueryModel();

      model->setQuery("SELECT* FROM abonnes");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Email"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("prenom"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("num tel"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("date de naissance"));
      model->setHeaderData(6, Qt::Horizontal, QObject::tr("type abonnement"));
       model->setHeaderData(6, Qt::Horizontal, QObject::tr("sexe"));

     return model;

 }
 bool sub::modifier(){
     bool test=false;
     QSqlQuery query;
     QString Cin_string= QString::number(Cin);
     QString TEL_string= QString::number(Num_tel);
       query.prepare("UPDATE abonnes SET email_abonnes=:email_abonnes,nom_abonnes=:nom_abonnes,prenom_abonnes=:prenom_abonnes,tel_abonnes=:tel_abonnes,ddn_abonnes=:ddn_abonnes,type_abonnement=:type_abonnement,sexe=:sexe WHERE cin_abonnes=:cin_abonnes");
       query.bindValue(":cin_abonnes",Cin_string);
       query.bindValue(":email_abonnes",Email);
       query.bindValue(":nom_abonnes", Nom);
       query.bindValue(":prenom_abonnes", Prenom);
       query.bindValue(":tel_abonnes", TEL_string);
       query.bindValue(":ddn_abonnes", ddn_abonnes);
       query.bindValue(":type_abonnement", type_abonnement);
       query.bindValue(":sexe",sexe);
       query.exec();
       test =true;
     return test ;
 }
 bool sub::verifierCin(int Cin)
 {  QSqlQuery  query;
     bool test=false;
       QString Cin_string=QString::number(Cin);
         query.prepare("SELECT * from abonnes where cin_abonnes=:cin_abonnes");
          query.bindValue(":cin_abonnes",Cin_string);
     if(query.exec()&&query.next())
     {     test=true;
          return test;
     }
     return test;
 }

 bool sub::verifvidestring(QString S)
 {
     bool test=true;
         if(S.length()==0)
          {  test=false;
             return test;}
         return test;
 }

 bool sub ::verifint(int S)
 {
     bool test=true;
         if(S==0)
          {  test=false;
             return test;}
         return test;

 }
 QSqlQueryModel * sub::afficher_tri_nom()
 {QSqlQueryModel * model= new QSqlQueryModel();

 model->setQuery("select * from abonnes order by nom_abonnes asc ");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("Email"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("prenom"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("num tel"));
 model->setHeaderData(5, Qt::Horizontal, QObject::tr("date de naissance"));
 model->setHeaderData(6, Qt::Horizontal, QObject::tr("type abonnement"));
 model->setHeaderData(7, Qt::Horizontal, QObject::tr("sexe"));



     return model;
 }

 QSqlQueryModel * sub::afficher_tri_prenom()
 {QSqlQueryModel * model= new QSqlQueryModel();

     model->setQuery("select * from abonnes order by prenom_abonnes asc ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("Email"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("prenom"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("num tel"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("date de naissance"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("type abonnement"));
     model->setHeaderData(7, Qt::Horizontal, QObject::tr("sexe"));



     return model;
 }

 QSqlQueryModel * sub::afficher_tri_ddn()
 {QSqlQueryModel * model= new QSqlQueryModel();

     model->setQuery("select * from abonnes order by ddn_abonnes asc ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("Email"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("prenom"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("num tel"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("date de naissance"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("type abonnement"));
     model->setHeaderData(7, Qt::Horizontal, QObject::tr("sexe"));




     return model;
 }
 QSqlQueryModel* sub::chercher_abonne(int index,QString text)
 {
 QSqlQuery query;
     QSqlQueryModel* model=new QSqlQueryModel();
     if(index==0)
    { query.prepare("SELECT * FROM abonnes where cin_abonnes like '"+text+"'");
      query.exec();
      model->setQuery(query);
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Email"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("prenom"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("num tel"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("date de naissance"));
      model->setHeaderData(6, Qt::Horizontal, QObject::tr("type abonnement"));
      model->setHeaderData(7, Qt::Horizontal, QObject::tr("sexe"));
      }
    if(index==1)
       {
        query.prepare("SELECT * FROM abonnes where nom_abonnes like '"+text+"'");
            query.exec();
            model->setQuery(query);
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Email"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("prenom"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("num tel"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("date de naissance"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("type abonnement"));
            model->setHeaderData(7, Qt::Horizontal, QObject::tr("sexe"));
    }


     return model;

 }
