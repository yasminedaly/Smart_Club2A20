#include "employee.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <vector>

employee::employee()
{


}

employee::employee(int cin1,QString nom1,QString prenom1,int tel1,QString email1,QString adresse1,QString diabetique1,int age1)
{
    cin=cin1;
    tel=tel1;
    nom=nom1;
    prenom=prenom1;
    age=age1;
    email=email1;
    adresse=adresse1;
    diabitique=diabetique1;
}



bool employee::ajouter_employee()
{
QSqlQuery query;

QString cin1 = QString::number(cin);
QString age1 = QString::number(age);
QString tel1 = QString::number(tel);


query.prepare("insert into employeeS(cin,nom,prenom,tel,email,adresse_locale,diabetique,age) values(:cin1,:nom,:prenom,:tel1,:email,:adresse,:diabitique,:age1)");
query.bindValue(":cin1",cin1);
query.bindValue(":nom",nom);
query.bindValue(":prenom",prenom);
query.bindValue(":tel1",tel1);
query.bindValue(":email",email);
query.bindValue(":adresse",adresse);
query.bindValue(":diabitique",diabitique);
query.bindValue(":age1",age1);






return query.exec();

}

QSqlQueryModel * employee::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from employees");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("tel"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("email"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("adresse_locale"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("diabetique"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("age"));
    return model;

}


  bool employee::modifier_employee()
  {

      QSqlQuery query;
      QString cin1 = QString::number(cin);
      QString age1 = QString::number(age);
      QString tel1 = QString::number(tel);

      query.prepare("update employeeS set nom=:nom,prenom=:prenom,tel=:tel1,email=:email,adresse_locale=:adresse,diabetique=:diabitique,age=:age1 where cin=:cin1");
      query.bindValue(":cin1",cin1);
      query.bindValue(":nom",nom);
      query.bindValue(":prenom",prenom);
      query.bindValue(":tel1",tel1);
      query.bindValue(":email",email);
      query.bindValue(":adresse",adresse);
      query.bindValue(":diabitique",diabitique);
      query.bindValue(":age1",age1);



  }


  bool employee::supp_employee(int cin)
  {

      QSqlQuery query;
      QString cin1 = QString::number(cin);
      query.prepare("Delete from employeeS  where cin =:cin1");
      query.bindValue(":cin1",cin1);
      return query.exec();

  }


  QSqlQueryModel * employee::combobox()
  {
      QSqlQueryModel * model = new QSqlQueryModel();
      //QString acc_ = QString::number(account);
      //QString perm=  QString::number(permissions);

      model->setQuery("select cin from employees");


      return model;
  }
