#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <vector>

class employee
{
public:
    employee();
    employee(int,QString,QString,int,QString,QString,QString,int);
     bool ajouter_employee();
     QSqlQueryModel * afficher();
       QSqlQueryModel * combobox();
     bool supp_employee(int);
     bool modifier_employee();

private:
    int cin;
    int tel;
    QString nom;
    QString prenom;
    int age;
    QString email;
    QString adresse;
    QString diabitique;

};

#endif // EMPLOYEE_H
