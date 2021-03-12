#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtSql>
#include <QSqlQuery>
//#include"connection.h"
#include <QSqlDatabase>
#include "evenement.h"
#include "Ticket.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_ajouter_2_clicked();

    void on_supp_event_clicked();

    void on_ajouter_clicked();

    void on_supp_clicked();

    void on_ajouter_3_clicked();

    void on_rechercher_clicked();
    void on_recherche_Ticket_clicked();

    void on_trie_clicked();

private:
    Ui::MainWindow *ui;
    Evenement  Etmp ;
    Ticket  Etmpp ;

};

#endif // MAINWINDOW_H
