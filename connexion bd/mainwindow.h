#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlQuery>
//#include"connection.h"
#include <QSqlDatabase>
#include "commande.h"
#include "bibliotheques.h"
#include <QTimer>
#include <QTextToSpeech>
#include <QMediaPlayer>
#include <QPropertyAnimation>

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMessageBox>
#include <QKeyEvent>
#include <QLayout>
#include <QSlider>

//Catch frame library
#include "getframe.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   // Ui::MainWindow *ui;

private slots:


    void on_horizontalSlider_2_valueChanged(int value);

    void on_comboBox_activated(int index);



    void on_pb_ajouter_clicked();

    //void on_pushButton_clicked();

    //void on_pushButton_2_clicked();

    //void on_pushButton_3_clicked();

    void on_pushButton_sup_clicked();

    void on_pushButton_mod_clicked();

    void on_pushButton_rch_clicked();

   // void on_pushButton_2_clicked();

    void on_Liv_ajouter_clicked();

    void on_liv_supprimer_clicked();

    void on_Liv_modifier_clicked();



    void on_pushButton_rch_livre_clicked();

    void on_tri_commande_clicked();

    void on_pushButton_tri_livre_clicked();

    void on_Historique_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();


    void on_pushButton_5_clicked();

    void on_recherche_clicked();

    void on_Liv_ajouter2_clicked();

    void showtime () ;

    void on_play_clicked();

    //Working with frames
    void GetFrame(QPixmap pix);

    //Key Work
    void keyPressEvent(QKeyEvent *ev);

    void on_horizontalSlider_2_actionTriggered(int action);

    void on_comboBox_activated(const QString &arg1);

    void on_endTime_linkActivated(const QString &link);

    void on_endTime_linkHovered(const QString &link);

    void fnClearPixmap();


    void on_comboBox_2_activated(const QString &arg1);

    void on_directory_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_comboBox_2_activated(int index);

private:
    void SetTimeLabel();

   Ui::MainWindow *ui;
   QPropertyAnimation *animation ;
     QPropertyAnimation *animation2 ;
    commande  Etmp ;
    commandeh Etmph ;
    Bibliotheques Etmpb ;
     QSqlQueryModel * model ;
     QMediaPlayer * erreur = new QMediaPlayer ;
     QString lng="fr";
     QMediaPlayer *click ;


     QMediaPlayer *player;
     QVideoWidget *videoWidget;
     QVBoxLayout *layout;
     QSlider *slider;
     bool pause = false;

     //Working with frames
     QMediaPlayer file_player;
     myQAbstractVideoSurface *vsur;
     QPixmap pixmap;
     int fileCounter = 0;


};

#endif // MAINWINDOW_H
