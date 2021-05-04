#include "database.h"
#include <QDebug>
database::database()
{

}
    bool database::createconnect()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Projet_2A20");
    db.setUserName("seif");
    db.setPassword("toor");

    if (db.open())
        test=true;
else

        qDebug()<< db.lastError().text();

     return  test;
}
