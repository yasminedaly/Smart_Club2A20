#include "connection.h"
#include <QDebug>

Connection::Connection(){}

bool Connection::createconnection()
{
    bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");//inserer le nom de la source de données ODBC
db.setUserName("genope");//inserer nom de l'utilisateur
db.setPassword("genope");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
void Connection::closeconnection(){db.close();}
