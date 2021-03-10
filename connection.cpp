#include "connection.h"
#include "QSqlDatabase"

//Test Tutorial Git

Connection::Connection()
{

}

bool Connection::createConnection()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("yasmine");
    db.setPassword("yasmine");

        if(db.open())
           test=true;
        return test;

}
