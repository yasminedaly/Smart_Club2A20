#include "connection.h"
//

Connection::Connection()
{

}

bool Connection::createconnection()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("source_chessmate");//inserer le nom de la source de données ODBC
db.setUserName("Yossra");//inserer nom de l'utilisateur
db.setPassword("esprit21");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





return  test;
}
void Connection::closeconnection()
{db.close();}
