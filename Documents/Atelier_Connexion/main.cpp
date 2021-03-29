#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include"stats.h"
#include "accueil.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // MainWindow w;
    Connection c;
    bool test=c.createconnection();
     MainWindow w;
     stats s;
     accueil g;
    if(test)
    {
       // w.show();
        g.show();
       // s.show();
      /*  QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel); */

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
