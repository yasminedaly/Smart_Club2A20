#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QPrinter>
#include <QPrintDialog>
#include "evenement.h"
#include"notification.h"
#include "smtp.h"
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QAction>
#include <QPropertyAnimation>
//#include <accueil.h>
#include "multiplication.h"
#include "player.h"
#include "plansza.h"
#include <listapytan.h>
#include <QtDebug>
#include <qtextcodec.h>
#include <glowne.h>
#include <QMediaPlayer>
#include <QtMultimedia/QSound>
#include <ticket.h>
#include<QtCharts/QChartView>
#include<QtCharts/QBarSeries>
#include<QtCharts/QBarSet>
#include<QtCharts/QLegend>
#include<QtCharts/QBarCategoryAxis>
#include<QtCharts/QHorizontalStackedBarSeries>
#include<QtCharts/QLineSeries>
#include<QtCharts/QCategoryAxis>
#include "mainmenu.h"
#include<QtCharts/QPieSeries>
#include<QtCharts/QPieSlice>
#include<QGridLayout>
#include <QtMultimedia/QSound>

#include <QSystemTrayIcon>
#include <QSequentialAnimationGroup>

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

   // void on_trier_clicked();

    void on_trie_2_clicked();

    void sendMail();
    void mailSent(QString);

    void on_envoyer_clicked();
    void statrefresh();


    void on_tableView_activated(const QModelIndex &index);

    void on_tableView_2_activated(const QModelIndex &index);

    //void on_retour_clicked();

    void on_clock_clicked();

    void on_Calculatrice_clicked();

    void on_Radio_clicked();

    void on_notepad_clicked();

    void on_test1_clicked();

    void on_test1_2_clicked();

    void on_play_music_clicked();


    void on_test1_3_clicked();
//void label();
//void label_9();

    void on_Jeu_echec_clicked();

private:
    Ui::MainWindow *ui;
    Evenement  Etmp ;
    Ticket  Etmpp ;
    notification n;
    //accueil a;
    QSystemTrayIcon * trayIcon;
     QSequentialAnimationGroup* animationGroup;
   // QPropertyAnimation *animation1;
    // QPropertyAnimation *animationn;
};

#endif // MAINWINDOW_H
