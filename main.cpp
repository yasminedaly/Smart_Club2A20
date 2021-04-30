#include "g_fournisseurs.h"

#include <QApplication>

#include "fournisseurs.h"
#include "factures.h"
#include "produits.h"
#include "connection.h"
#include<QDate>
#include <QDebug>
#include <QMessageBox>


int main(int argc, char *argv[])
{
    qputenv("QT_SCALE_FACTOR", QByteArray("1"));
    QApplication a(argc, argv);


    Connection c;
    bool test=c.createconnect();
    G_Fournisseurs w;

    if(test)
    {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
        QObject::tr("connection successful.\n" "Click Cancel to exit."), QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
        QObject::tr("connection failed.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
    w.show();
    return a.exec();
}
