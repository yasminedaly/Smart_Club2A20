#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection C;
    bool test = C.createConnection();
    MainWindow w;
if(test)
   {

    qDebug() <<"Connecxion réussite";
    w.show();
    QMessageBox::information(nullptr,QObject::tr("database is open"),
                             QObject::tr("Connexion successfull:\n"
                                         "click ok to exit"), QMessageBox::Ok);
}
else
   {
     qDebug() <<"Erreur de connexion";
    QMessageBox::critical(nullptr,QObject::tr("database is not open"),
                             QObject::tr("Connexion failed:\n"
                                         "click cancel to exit"), QMessageBox::Cancel);
}
    return a.exec();
}
