#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QPrinter>
#include <QPrintDialog>
#include "evenement.h"
#include "Ticket.h"
#include"notification.h"
#include "smtp.h"
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QAction>


#include<QtCharts/QChartView>
#include<QtCharts/QBarSeries>
#include<QtCharts/QBarSet>
#include<QtCharts/QLegend>
#include<QtCharts/QBarCategoryAxis>
#include<QtCharts/QHorizontalStackedBarSeries>
#include<QtCharts/QLineSeries>
#include<QtCharts/QCategoryAxis>

#include<QtCharts/QPieSeries>
#include<QtCharts/QPieSlice>
#include<QGridLayout>
#include <QtMultimedia/QSound>

#include <QSystemTrayIcon>

QT_CHARTS_USE_NAMESPACE
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

    void print(QPrinter *printer);

    void on_ajouter_2_clicked();

    void on_supp_event_clicked();

    void on_ajouter_clicked();

    void on_supp_clicked();

    void on_ajouter_3_clicked();

    void on_rechercher_clicked();
    void on_recherche_Ticket_clicked();

    void on_trie_clicked();

    void on_PDF_clicked();

    void on_Modifier_Ticket_clicked();

    void on_le_id_textChanged(const QString &arg1);

    void on_le_id_2_textChanged(const QString &arg1);

    void on_tabevenement_currentChanged(int index);

    void on_trier_clicked();

    void on_trie_2_clicked();

    void sendMail();
    void mailSent(QString);

    void on_envoyer_clicked();
    void statrefresh();


    void on_tableView_activated(const QModelIndex &index);

    void on_tableView_2_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Evenement  Etmp ;
    Ticket  Etmpp ;
    notification n;
    QSystemTrayIcon * trayIcon;

};

#endif // MAINWINDOW_H
