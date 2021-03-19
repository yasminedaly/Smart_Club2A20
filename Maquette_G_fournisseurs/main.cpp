#include "mainwindow.h"

#include <QApplication>

#include "fournisseurs.h"
#include "factures.h"
#include "produits.h"
#include "connection.h"

#include <QDebug>
#include <QMessageBox>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Connection c;
    bool test=c.createconnect();
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

