#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

db.setDatabaseName("projet_2A");
db.setUserName("khaled");
db.setPassword("esprit2019");



if (db.open())
test=true;





    return  test;
}
