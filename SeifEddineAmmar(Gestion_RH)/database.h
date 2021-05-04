#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>


class database
{
public:
    database();
    bool createconnect();
};


#endif // DATABASE_H
