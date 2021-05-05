#include "mainwindowyosra.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include"stats.h"
#include "analogclock.h"
#include "calculator.h"
#include "widget.h"
#include "note.h"
#include "sudoku_solver.h"
#include "player.h"
#include "plansza.h"
#include <listapytan.h>
#include <QtDebug>
#include <qtextcodec.h>
#include <glowne.h>
#include "mainmenu.h"
/**
 * \mainpage
 * \par Gra
 * Gra Quiz.
 * \author Osinska Agnieszka
 * \date 2015.06.07
 * \version 2.0
 * \a osinska@student.agh.edu.pl
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QIcon("./images/icon.png");
   // MainWindow w;
    Connection c;
    bool test=c.createconnection();
     MainWindowyosra w;
     stats s;
   //  accueil g;
     AnalogClock clock;
     calculator h;
       Widget q;
        note n;
   Sudoku_Solver  su;
   multiplication mu;
   player p;
     glowne d;
     MainMenu C;

        //clock.show();
    if(test)
    {
        w.show();
        //g.show();
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
